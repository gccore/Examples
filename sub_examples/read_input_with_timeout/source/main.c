/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @another_ghasem
 * g1999ramezani@gmail.com
 */

#include <stdatomic.h>
#include <stdbool.h>
#include <threads.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

typedef struct {
  char value;
  atomic_bool read_flag;
} input_value_t;

int read_input_function(void* value) {
  input_value_t* value_struct = (input_value_t*) value;
  scanf("%c", &value_struct->value);
  atomic_store_explicit(&value_struct->read_flag, true, memory_order_release);

  return thrd_success;
}

#define TIME_LIMIT_S 2
#define ELPACED_TIME(start) \
  ((double)(start = clock() - start) / CLOCKS_PER_SEC)

int main() {
  input_value_t value = {.value = ' ', .read_flag = false};
  thrd_t read_input_thread;

  time_t start_time = clock();
  if (thrd_success == thrd_create(&read_input_thread, read_input_function, (void*) &value)) {
    while (!atomic_load_explicit(&value.read_flag, memory_order_acquire)
           &&  ELPACED_TIME(start_time) < TIME_LIMIT_S) {
      thrd_yield();
    }

    if (! value.read_flag) {
      printf("Timeout.\n");
    } else {
      printf("Your value: %c\n.", value.value);
    }
  }
}

