#ifndef MANIFOLD2_MANIFOLD_H_
#define MANIFOLD2_MANIFOLD_H_

#include "types.h"

#include "Octree.h"

class Manifold {
public:
	Manifold();
	~Manifold();
	void ProcessManifold(const MatrixD& V,const MatrixD& VC, const MatrixI& F, int depth,
		MatrixD* out_V, MatrixD* out_VC, MatrixI* out_F);

protected:
	void BuildTree(int resolution);
	void CalcBoundingBox();
	void ConstructManifold();
	bool SplitGrid(const std::vector<Vector4i>& nface_indices,
		std::map<GridIndex,int>& vcolor,
		std::vector<Vector3>& nvertices,
		std::vector<Vector3>& nvertex_colors,
		std::vector<std::set<int> >& v_faces,
		std::vector<Vector3i>& triangles);

private:	
	Octree* tree_;
	Vector3 min_corner_, max_corner_;
	MatrixD V_;
	MatrixD VC_;
	MatrixI F_;

	std::vector<Vector3> vertices_;
	std::vector<Vector3> vertex_colors_;
	std::vector<Vector3i> face_indices_;
	std::vector<GridIndex > v_info_;

};

#endif