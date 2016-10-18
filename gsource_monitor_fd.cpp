#include <glib.h>

int main()
{
  GSourceFuncs no_funcs = {
    NULL, NULL, return_true
  };

  GSource *source_a;
  GSource *source_b;

  gpointer tag1, tag2;

  gint fds_a[2];
  gint fds_b[2];

  pipe (fds_a);
  pipe (fds_b);

  source_a = g_source_new (&no_funcs, sizeof (FlagSource));
  source_b = g_source_new (&no_funcs, sizeof (FlagSource));

  /* attach a source with more than one fd */
  g_source_add_unix_fd (source_a, fds_a[0], G_IO_IN);
  g_source_add_unix_fd (source_a, fds_a[1], G_IO_OUT);
  g_source_attach (source_a, NULL);
  assert_main_context_state (2,
                             fds_a[0], G_IO_IN, 0,
                             fds_a[1], G_IO_OUT, 0);
  assert_not_flagged (source_a);

  /* attach a higher priority source with no fds */
  g_source_set_priority (source_b, G_PRIORITY_HIGH);
  g_source_attach (source_b, NULL);
  assert_main_context_state (2,
                             fds_a[0], G_IO_IN, G_IO_IN,
                             fds_a[1], G_IO_OUT, 0);
  assert_flagged (source_a);
  assert_not_flagged (source_b);
  clear_flag (source_a);

  /* add some fds to the second source, while attached */
  tag1 = g_source_add_unix_fd (source_b, fds_b[0], G_IO_IN);
  tag2 = g_source_add_unix_fd (source_b, fds_b[1], G_IO_OUT);
  assert_main_context_state (4,
                             fds_a[0], G_IO_IN, 0,
                             fds_a[1], G_IO_OUT, G_IO_OUT,
                             fds_b[0], G_IO_IN, 0,
                             fds_b[1], G_IO_OUT, G_IO_OUT);
  /* only 'b' (higher priority) should have dispatched */
  assert_not_flagged (source_a);
  assert_flagged (source_b);
  clear_flag (source_b);

  /* change our events on b to the same as they were before */
  g_source_modify_unix_fd (source_b, tag1, G_IO_IN);
  g_source_modify_unix_fd (source_b, tag2, G_IO_OUT);
  assert_main_context_state (4,
                             fds_a[0], G_IO_IN, 0,
                             fds_a[1], G_IO_OUT, G_IO_OUT,
                             fds_b[0], G_IO_IN, 0,
                             fds_b[1], G_IO_OUT, G_IO_OUT);
  assert_not_flagged (source_a);
  assert_flagged (source_b);
  clear_flag (source_b);

  /* now reverse them */
  g_source_modify_unix_fd (source_b, tag1, G_IO_OUT);
  g_source_modify_unix_fd (source_b, tag2, G_IO_IN);
  assert_main_context_state (4,
                             fds_a[0], G_IO_IN, 0,
                             fds_a[1], G_IO_OUT, G_IO_OUT,
                             fds_b[0], G_IO_OUT, 0,
                             fds_b[1], G_IO_IN, 0);
  /* 'b' had no events, so 'a' can go this time */
  assert_flagged (source_a);
  assert_not_flagged (source_b);
  clear_flag (source_a);

  /* remove one of the fds from 'b' */
  g_source_remove_unix_fd (source_b, tag1);
  assert_main_context_state (3,
                             fds_a[0], G_IO_IN, 0,
                             fds_a[1], G_IO_OUT, 0,
                             fds_b[1], G_IO_IN, 0);
  assert_not_flagged (source_a);
  assert_not_flagged (source_b);

  /* remove the other */
  g_source_remove_unix_fd (source_b, tag2);
  assert_main_context_state (2,
                             fds_a[0], G_IO_IN, 0,
                             fds_a[1], G_IO_OUT, 0);
  assert_not_flagged (source_a);
  assert_not_flagged (source_b);

  /* destroy the sources */
  g_source_destroy (source_a);
  g_source_destroy (source_b);
  assert_main_context_state (0);

  g_source_unref (source_a);
  g_source_unref (source_b);
  close (fds_a[0]);
  close (fds_a[1]);
  close (fds_b[0]);
  close (fds_b[1]);
}
