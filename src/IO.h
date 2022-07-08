#ifndef MANIFOLD2_IO_H_
#define MANIFOLD2_IO_H_

#include "types.h"

void ReadOBJ(const char* filename, MatrixD* V, MatrixD* VC, MatrixI* F);
void WriteOBJ(const char* filename, const MatrixD& V, const MatrixD& VC, const MatrixI& F);

#endif