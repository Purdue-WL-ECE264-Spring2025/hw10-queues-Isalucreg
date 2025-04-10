#include <stdlib.h>
#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue* q, int value) {
    q->list = insert_at_tail(q->list, value);
}

int dequeue(struct queue* q) {
    int value;
    q->list = remove_from_head(q->list, &value);
    return value;
}

int bfs(struct game_state* start, struct game_state* target) {
    struct queue q = {NULL};
    int visited[FACTORIAL_16] = {0};

    int start_serial = serialize(start);
    int target_serial = serialize(target);

    enqueue(&q, start_serial);
    visited[start_serial] = 1;

    while (q.list) {
        int cur_serial = dequeue(&q);

        if (cur_serial == target_serial) {
            struct game_state cur_state;
            deserialize(cur_serial, &cur_state);
            free_list(q.list);
            return cur_state.number_of_moves;
        }

        struct game_state cur_state;
        deserialize(cur_serial, &cur_state);

        for (int i = 0; i < 4; i++) {
            struct game_state next_state = cur_state;
            if (make_move(&next_state, i)) {
                int next_serial = serialize(&next_state);
                if (!visited[next_serial]) {
                    visited[next_serial] = 1;
                    enqueue(&q, next_serial);
                }
            }
        }
    }

    free_list(q.list);
    return -1; // unreachable in solvable puzzles
}
