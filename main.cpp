#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>

int main() {

  std::fstream file_out;
  //    char *filename=new char[20];
  char filename[100];
  double ar_cur[50]{0};
  double ar_nx[50]{0};
  double ar_fin[50]{0};
  int k = 0;
  double _if_plus_[50]{0};
  double _if_minus_[50]{0};
  double kappa_1 = 0, kappa_2 = 0;
  for (int i = 0; i < 50; i++) {
    ar_cur[i] = std::sqrt(std::exp(-(i - 2) * (i - 2)));
  }
  for (int v = -5; v < 0; v++) {
    kappa_1 += v * std::sqrt(std::exp(-v * v));
  }
  for (int v = 1; v < 6; v++) {
    kappa_2 += v * std::sqrt(std::exp(-v * v));
  }
  for (int i = 0; i < 6; i++) {
    _if_minus_[i] = std::sqrt(std::exp(-i * i));
  }
  for (int i = 0; i < 6; i++) {

    _if_plus_[i] = -std::sqrt(std::exp(-i * i)) * kappa_1 / kappa_2;
  }
  ar_cur[49] = 0;
  for (int t = 1; t < 100; t++) {

    sprintf(filename, "data/out_%03d.txt", t);
    file_out.open(filename, std::fstream::out);
    for (int v = -5; v < 6; v++) {

      double G = std::abs(v * 0.1);
      if (v > 0) {

        for (int j = 1; j < 50; j++) {

          ar_nx[j] = ar_cur[j] - G * (ar_cur[j] - ar_cur[j - 1]);
          ar_fin[j] += ar_nx[j];
        }
        ar_fin[0] = ar_nx[0] = _if_plus_[v - 1];
      }
      if (v < 0) {

        for (int j = 1; j < 49; j++) {

          ar_nx[j] = ar_cur[j + 1] - G * (ar_cur[j + 1] - ar_cur[j]);
          ar_fin[j] += ar_nx[j];
        }
        ar_fin[49] = ar_nx[49] = _if_minus_[std::abs(v) - 1];
      }
      if (v == 0) {

        for (int j = 0; j < 50; j++) {

          ar_nx[j] = ar_cur[j];
          ar_fin[j] += ar_nx[j];
        }
      }
    }
    k = 0;
    for (int i = 0; i < 50; i++) {
      if (ar_fin[i] != 1 && ar_fin[i] > 0) {
        file_out << k << '\t' << std::abs(ar_fin[i]) << std::endl;
        ar_fin[i] = 0;
      }
      k++;
    }
    file_out << " " << std::endl;
    for (int i = 0; i < 50; i++) {

      ar_cur[i] = ar_nx[i];
    }
    file_out.close();
  }
  return 0;
}
