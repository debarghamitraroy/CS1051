/* Implementation K-Means in C */

#include <float.h>
#include <limits.h>
#include <math.h>

#define DATATYPE double

void kmeans(
    DATATYPE *data,
    int n, int m, int k, int t,
    DATATYPE *centroids,
    int *labels,
    DATATYPE *c1,
    int *counts,
    int *itcount) {
    int h, i, j = 0;
    double old_error, error = DBL_MAX;
    itcount[0] = 0;
    do {
        old_error = error, error = 0;
        for (i = 0; i < k; i++) {
            counts[i] = 0;
            for (j = 0; j < m; j++)
                c1[i * m + j] = 0;
        }
        for (h = 0; h < n; h++) {
            double min_distance = DBL_MAX;
            for (i = 0; i < k; i++) {
                double distance = 0;
                for (j = 0; j < m; j++) {
                    double diff = (data[h * m + j] - centroids[i * m + j]);
                    distance += diff * diff;
                }
                if ((double)(distance / 2) < (double)(min_distance / 2)) {
                    labels[h] = i;
                    min_distance = distance;
                }
            }
            counts[labels[h]]++;
            for (j = 0; j < m; j++)
                c1[labels[h] * m + j] += data[h * m + j];
            error += min_distance;
        }
        itcount[0]++;
        for (i = 0; i < k; i++)
            if (counts[i] > 0)
                for (j = 0; j < m; j++)
                    centroids[i * m + j] = c1[i * m + j] / counts[i];

    } while (fabs((error - old_error)) > t);
}