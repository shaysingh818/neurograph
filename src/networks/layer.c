#include "includes/layer.h"

void serialize_layer(char* filename, layer_t *layer) {
    FILE* file = fopen(filename, "wb"); // Open the file for binary write

    if (file != NULL) {
        // Write the neural network structure to the file
        fwrite(layer, sizeof(layer_t*), 1, file);

        fclose(file);
    } else {
        printf("Error: Unable to open the file for writing.\n");
    }
}

void deserialize_layer(char* filename, layer_t *layer) {
    FILE* file = fopen(filename, "rb"); // Open the file for binary read

    if (file != NULL) {
        // Read the neural network structure from the file
        fread(layer, sizeof(layer_t*), 1, file);

        fclose(file);
    } else {
        printf("Error: Unable to open the file for reading.\n");
    }
}