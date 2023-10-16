#include "computation_graph.h"


/* multiplication */
value_t *mat_mul(computation_graph_t *graph, value_t *x, value_t *y); 
mat_t *mat_mul_forward(value_t *val); 
mat_t *mat_mul_backward(value_t *val); 


/* scale add */
value_t *scale_add_mat(computation_graph_t *graph, value_t *x, value_t *y); 
mat_t *scale_add_forward(value_t *val); 
mat_t *scale_add_backward(value_t *val);


/* apply loss  */
value_t *apply_loss(
    computation_graph_t *graph, 
    value_t *set_val,
    double(*loss)(double val), 
	mat_t*(*loss_prime)(mat_t *val)
); 
mat_t *apply_loss_forward(value_t *val); 
mat_t *apply_loss_backward(value_t *val);

