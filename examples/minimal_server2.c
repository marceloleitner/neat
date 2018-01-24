#include <neat.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

/*
 * Note: Do not edit this file without updating the line numbers in the tutorial
 * in the documentation.
 */

static neat_error_code on_writable(struct neat_flow_operations *ops);
static neat_error_code on_all_written(struct neat_flow_operations *ops);

static neat_error_code
on_readable(struct neat_flow_operations *ops)
{
    uint32_t bytes_read = 0;
    unsigned char buffer[32];

    if (neat_read(ops->ctx, ops->flow, buffer, 31, &bytes_read, NULL, 0) == NEAT_OK) {
        buffer[bytes_read] = 0;
        fprintf(stdout, "Read %u bytes:\n%s\n", bytes_read, buffer);
    }

    ops->on_readable = NULL;
    ops->on_writable = on_writable;
    ops->on_all_written = on_all_written;
    neat_set_operations(ops->ctx, ops->flow, ops);

    return NEAT_OK;
}

static neat_error_code
on_writable(struct neat_flow_operations *ops)
{
    const unsigned char message[] = "Hello, this is NEAT!";
    neat_write(ops->ctx, ops->flow, message, 20, NULL, 0);

    ops->on_writable = NULL;
    ops->on_readable = NULL;
    ops->on_all_written = on_all_written;
    neat_set_operations(ops->ctx, ops->flow, ops);

    return NEAT_OK;
}

static neat_error_code
on_all_written(struct neat_flow_operations *ops)
{
    ops->on_readable = NULL;
    ops->on_writable = NULL;
    ops->on_all_written = NULL;
    neat_set_operations(ops->ctx, ops->flow, ops);

    neat_close(ops->ctx, ops->flow);

    return NEAT_OK;
}

static neat_error_code
on_connected(struct neat_flow_operations *ops)
{
    ops->on_readable = on_readable;
    neat_set_operations(ops->ctx, ops->flow, ops);

    return NEAT_OK;
}

int
main(int argc, char *argv[])
{
    struct neat_ctx *ctx;
    struct neat_flow *flow;
    struct neat_flow_operations ops;

    ctx  = neat_init_ctx();
    if (!ctx) {
        fprintf(stderr, "neat_init_ctx failed\n");
        return EXIT_FAILURE;
    }

    flow = neat_new_flow(ctx);
    if (!flow) {
        fprintf(stderr, "neat_new_flow failed\n");
        return EXIT_FAILURE;
    }
    
    memset(&ops, 0, sizeof(ops));

    ops.on_connected = on_connected;
    neat_set_operations(ctx, flow, &ops);

    if (neat_accept(ctx, flow, 5000, NULL, 0)) {
        fprintf(stderr, "neat_accept failed\n");
        return EXIT_FAILURE;
    }

    neat_start_event_loop(ctx, NEAT_RUN_DEFAULT);

    return EXIT_SUCCESS;
}
