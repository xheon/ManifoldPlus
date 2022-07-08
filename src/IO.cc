#include "IO.h"

#include <igl/readOFF.h>
#include <fstream>
#include <vector>

void ReadOBJ(const char* filename, MatrixD* V, MatrixD* VC, MatrixI* F) {
	int len = strlen(filename);
	if (strcmp(filename + (len - 3), "off") == 0) {
		igl::readOFF(filename, *V, *F);
		return;
	}
	char buffer[1024];
	std::ifstream is(filename);
	std::vector<Vector3> vertices;
	std::vector<Vector3> vertex_colors;
	std::vector<Vector3i> faces;
	while (is >> buffer) {
		if (strcmp(buffer, "v") == 0) {
			Vector3 v;
			is >> v[0] >> v[1] >> v[2];
			vertices.push_back(v);

            Vector3 vc;
            is >> vc[0] >> vc[1] >> vc[2];
            vertex_colors.push_back(vc);
		}
		if (strcmp(buffer, "f") == 0) {
			Vector3i f;
			for (int j = 0; j < 3; ++j) {
				is >> buffer;
				int t = 0;
				int k = 0;
				while (buffer[k] >= '0' && buffer[k] <= '9') {
					t = t * 10 + (buffer[k] - '0');
					k += 1;
				}
				f[j] = t - 1;
			}
			faces.push_back(f);
		}
	}
	V->resize(vertices.size(), 3);
	F->resize(faces.size(), 3);
	memcpy(V->data(), vertices.data(), sizeof(Vector3) * vertices.size());
	memcpy(F->data(), faces.data(), sizeof(Vector3i) * faces.size());

    VC->resize(vertices.size(), 3);
    memcpy(VC->data(), vertex_colors.data(), sizeof(Vector3) * vertices.size());
}

void WriteOBJ(const char* filename, const MatrixD& V, const MatrixD& VC, const MatrixI& F) {
	std::ofstream os(filename);
	for (int i = 0; i < V.rows(); ++i) {
		auto& v = V.row(i);
		auto& vc = VC.row(i);
		os << "v " << v[0] << " " << v[1] << " " << v[2] << " " << vc[0] << " " << vc[1] << " " << vc[2] << "\n";
	}
	for (int i = 0; i < F.rows(); ++i) {
		auto& f = F.row(i);
		os << "f " << f[0] + 1 << " " << f[1] + 1 << " " << f[2] + 1 << "\n";
	}
	os.close();
}
