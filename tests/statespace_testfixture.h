// Copyright 2019 Google LLC. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef STATESPACE_TESTFIXTURE_H_
#define STATESPACE_TESTFIXTURE_H_

#include <array>
#include <cmath>
#include <complex>
#include <cstdint>
#include <string>

#include "gtest/gtest.h"

#include "../lib/circuit_qsim_parser.h"
#include "../lib/fuser_basic.h"
#include "../lib/gates_qsim.h"
#include "../lib/io.h"
#include "../lib/run_qsim.h"

namespace qsim {

constexpr char provider[] = "statespace_test";

constexpr char circuit_string[] =
R"(20
0 h 0
0 h 1
0 h 2
0 h 3
0 h 4
0 h 5
0 h 6
0 h 7
0 h 8
0 h 9
0 h 10
0 h 11
0 h 12
0 h 13
0 h 14
0 h 15
0 h 16
0 h 17
0 h 18
0 h 19
1 cz 0 1
1 cz 7 8
1 cz 10 11
1 cz 17 18
2 cz 2 3
2 cz 5 6
2 cz 12 13
2 cz 15 16
2 t 0
2 t 1
2 t 7
2 t 8
2 t 10
2 t 11
2 t 17
2 t 18
3 cz 5 10
3 cz 7 12
3 cz 9 14
3 t 2
3 t 3
3 t 6
3 t 13
3 t 15
3 t 16
4 cz 6 11
4 cz 8 13
4 t 5
4 x_1_2 7
4 t 9
4 y_1_2 10
4 t 12
4 t 14
5 cz 1 2
5 cz 8 9
5 cz 11 12
5 cz 18 19
5 y_1_2 6
5 x_1_2 13
6 cz 3 4
6 cz 6 7
6 cz 13 14
6 cz 16 17
6 y_1_2 1
6 y_1_2 2
6 y_1_2 8
6 y_1_2 9
6 y_1_2 11
6 y_1_2 12
6 y_1_2 18
6 t 19
7 cz 0 5
7 cz 2 7
7 cz 4 9
7 cz 11 16
7 cz 13 18
7 x_1_2 3
7 x_1_2 6
7 y_1_2 14
7 x_1_2 17
8 cz 1 6
8 cz 3 8
8 cz 10 15
8 cz 12 17
8 cz 14 19
8 x_1_2 0
8 x_1_2 2
8 t 4
8 x_1_2 5
8 y_1_2 7
8 t 9
8 x_1_2 11
8 t 13
8 y_1_2 16
8 x_1_2 18
9 cz 0 1
9 cz 7 8
9 cz 10 11
9 cz 17 18
9 y_1_2 3
9 t 6
9 t 12
9 t 14
9 y_1_2 15
9 x_1_2 19
10 cz 2 3
10 cz 5 6
10 cz 12 13
10 cz 15 16
10 t 0
10 x_1_2 1
10 t 7
10 x_1_2 8
10 t 10
10 t 11
10 y_1_2 17
10 t 18
11 cz 5 10
11 cz 7 12
11 cz 9 14
11 t 2
11 x_1_2 3
11 x_1_2 6
11 y_1_2 13
11 x_1_2 15
11 t 16
12 cz 6 11
12 cz 8 13
12 t 5
12 y_1_2 7
12 y_1_2 9
12 y_1_2 10
12 x_1_2 12
12 y_1_2 14
13 cz 1 2
13 cz 8 9
13 cz 11 12
13 cz 18 19
13 y_1_2 6
13 t 13
14 cz 3 4
14 cz 6 7
14 cz 13 14
14 cz 16 17
14 t 1
14 y_1_2 2
14 t 8
14 x_1_2 9
14 y_1_2 11
14 y_1_2 12
14 x_1_2 18
14 t 19
15 cz 0 5
15 cz 2 7
15 cz 4 9
15 cz 11 16
15 cz 13 18
15 t 3
15 x_1_2 6
15 t 14
15 x_1_2 17
16 cz 1 6
16 cz 3 8
16 cz 10 15
16 cz 12 17
16 cz 14 19
16 y_1_2 0
16 x_1_2 2
16 x_1_2 4
16 x_1_2 5
16 x_1_2 7
16 y_1_2 9
16 t 11
16 y_1_2 13
16 x_1_2 16
16 y_1_2 18
17 cz 0 1
17 cz 7 8
17 cz 10 11
17 cz 17 18
17 x_1_2 3
17 t 6
17 t 12
17 x_1_2 14
17 t 15
17 x_1_2 19
18 cz 2 3
18 cz 5 6
18 cz 12 13
18 cz 15 16
18 x_1_2 0
18 y_1_2 1
18 y_1_2 7
18 y_1_2 8
18 t 10
18 y_1_2 11
18 t 17
18 t 18
19 cz 5 10
19 cz 7 12
19 cz 9 14
19 t 2
19 y_1_2 3
19 y_1_2 6
19 t 13
19 x_1_2 15
19 y_1_2 16
20 cz 6 11
20 cz 8 13
20 t 5
20 x_1_2 7
20 x_1_2 9
20 y_1_2 10
20 y_1_2 12
20 y_1_2 14
21 cz 1 2
21 cz 8 9
21 cz 11 12
21 cz 18 19
21 t 6
21 x_1_2 13
22 cz 3 4
22 cz 6 7
22 cz 13 14
22 cz 16 17
22 x_1_2 1
22 y_1_2 2
22 x_1_2 8
22 y_1_2 9
22 x_1_2 11
22 t 12
22 y_1_2 18
22 y_1_2 19
23 cz 0 5
23 cz 2 7
23 cz 4 9
23 cz 11 16
23 cz 13 18
23 t 3
23 x_1_2 6
23 x_1_2 14
23 x_1_2 17
24 cz 1 6
24 cz 3 8
24 cz 10 15
24 cz 12 17
24 cz 14 19
24 y_1_2 0
24 x_1_2 2
24 t 4
24 x_1_2 5
24 t 7
24 x_1_2 9
24 t 11
24 t 13
24 t 16
24 t 18
25 cz 0 1
25 cz 7 8
25 cz 10 11
25 cz 17 18
25 y_1_2 3
25 y_1_2 6
25 y_1_2 12
25 t 14
25 t 15
25 t 19
26 cz 2 3
26 cz 5 6
26 cz 12 13
26 cz 15 16
26 x_1_2 0
26 t 1
26 y_1_2 7
26 y_1_2 8
26 x_1_2 10
26 y_1_2 11
26 y_1_2 17
26 x_1_2 18
27 cz 5 10
27 cz 7 12
27 cz 9 14
27 y_1_2 2
27 x_1_2 3
27 t 6
27 y_1_2 13
27 x_1_2 15
27 x_1_2 16
28 cz 6 11
28 cz 8 13
28 t 5
28 x_1_2 7
28 t 9
28 t 10
28 t 12
28 y_1_2 14
29 cz 1 2
29 cz 8 9
29 cz 11 12
29 cz 18 19
29 x_1_2 6
29 x_1_2 13
30 cz 3 4
30 cz 6 7
30 cz 13 14
30 cz 16 17
30 x_1_2 1
30 t 2
30 x_1_2 8
30 y_1_2 9
30 t 11
30 y_1_2 12
30 y_1_2 18
30 y_1_2 19
)";

template <typename StateSpace>
void TestNormSmall() {
  using State = typename StateSpace::State;

  constexpr unsigned num_qubits1 = 1;
  StateSpace state_space1(num_qubits1, 1);
  State state1 = state_space1.CreateState();
  state_space1.SetStateZero(state1);
  EXPECT_NEAR(state_space1.Norm(state1), 1, 1e-6);
  state_space1.SetStateUniform(state1);
  EXPECT_NEAR(state_space1.Norm(state1), 1, 1e-6);

  constexpr unsigned num_qubits2 = 2;
  StateSpace state_space2(num_qubits2, 1);
  State state2 = state_space2.CreateState();
  state_space2.SetStateZero(state2);
  EXPECT_NEAR(state_space2.Norm(state2), 1, 1e-6);
  state_space2.SetStateUniform(state2);
  EXPECT_NEAR(state_space2.Norm(state2), 1, 1e-6);

  constexpr unsigned num_qubits3 = 3;
  StateSpace state_space3(num_qubits3, 1);
  State state3 = state_space3.CreateState();
  state_space3.SetStateZero(state3);
  EXPECT_NEAR(state_space3.Norm(state3), 1, 1e-6);
  state_space3.SetStateUniform(state3);
  EXPECT_NEAR(state_space3.Norm(state3), 1, 1e-6);
}

template <typename StateSpace>
void TestNormAndInnerProductSmall() {
  constexpr unsigned num_qubits = 2;
  constexpr uint64_t size = uint64_t{1} << num_qubits;

  using State = typename StateSpace::State;
  using fp_type = typename StateSpace::fp_type;

  StateSpace state_space(num_qubits, 1);

  State state1 = state_space.CreateState();
  State state2 = state_space.CreateState();

  EXPECT_EQ(state_space.IsNull(state1), false);
  EXPECT_EQ(state_space.IsNull(state2), false);
  EXPECT_EQ(state_space.Size(state1), size);
  EXPECT_EQ(state_space.Size(state2), size);

  state_space.SetAllZeros(state1);
  state_space.SetAllZeros(state2);

  std::array<fp_type, size> values1 = {0.25, 0.3, 0.35, 0.1};
  std::array<fp_type, size> values2 = {0.4, 0.15, 0.2, 0.25};

  std::complex<double> inner_product0 = 0;

  for (uint64_t i = 0; i < size; ++i) {
    fp_type c = std::cos(i);
    fp_type s = std::sin(i);
    fp_type r1 = std::sqrt(values1[i]);
    fp_type r2 = std::sqrt(values2[i]);
    std::complex<fp_type> cvalue1 = {r1 * c, -r1 * s};
    std::complex<fp_type> cvalue2 = {r2 * c, r2 * s};

    state_space.SetAmpl(state1, i, cvalue1);
    state_space.SetAmpl(state2, i, cvalue2);

    inner_product0 += std::conj(cvalue1) * cvalue2;
  }

  EXPECT_NEAR(state_space.Norm(state1), 1, 1e-6);
  EXPECT_NEAR(state_space.Norm(state2), 1, 1e-6);

  auto inner_product = state_space.InnerProduct(state1, state2);
  EXPECT_NEAR(std::real(inner_product), std::real(inner_product0), 1e-6);
  EXPECT_NEAR(std::imag(inner_product), std::imag(inner_product0), 1e-6);

  auto real_inner_product = state_space.RealInnerProduct(state1, state2);
  EXPECT_NEAR(real_inner_product, std::real(inner_product0), 1e-6);
}

template <typename Simulator>
void TestNormAndInnerProduct() {
  unsigned depth = 8;

  std::stringstream ss(circuit_string);
  Circuit<GateQSim<float>> circuit;
  EXPECT_EQ(CircuitQsimParser<IO>::FromStream(depth, provider, ss, circuit), true);
  circuit.gates.emplace_back(GateT<float>::Create(depth + 1, 0));

  using StateSpace = typename Simulator::StateSpace;
  using State = typename StateSpace::State;
  using Runner = QSimRunner<IO, BasicGateFuser<GateQSim<float>>, Simulator>;

  StateSpace state_space(circuit.num_qubits, 1);
  State state0 = state_space.CreateState();

  EXPECT_EQ(state_space.IsNull(state0), false);

  auto measure = [&state0](unsigned k,
                           const StateSpace& state_space, const State& state) {
    if (k == 0) {
      EXPECT_NEAR(state_space.Norm(state), 1, 1e-5);

      state_space.CopyState(state, state0);
    } else if (k == 1) {
      auto inner_product = state_space.InnerProduct(state0, state);
      EXPECT_NEAR(std::real(inner_product), 0.5 + 0.5 / std::sqrt(2), 1e-5);
      EXPECT_NEAR(std::imag(inner_product), 0.5 / std::sqrt(2), 1e-5);

      auto real_inner_product = state_space.RealInnerProduct(state0, state);
      EXPECT_NEAR(real_inner_product, 0.5 + 0.5 / std::sqrt(2), 1e-5);
    }
  };

  typename Runner::Parameter param;
  param.num_threads = 1;
  param.verbosity = 0;

  std::vector<unsigned> times{depth, depth + 1};
  EXPECT_EQ(Runner::Run(param, times, circuit, measure), true);
}

template <typename StateSpace>
void TestSamplingSmall() {
  uint64_t num_samples = 2000000;
  constexpr unsigned num_qubits = 3;
  constexpr uint64_t size = uint64_t{1} << num_qubits;

  using State = typename StateSpace::State;

  StateSpace state_space(num_qubits, 1);
  State state = state_space.CreateState();

  EXPECT_EQ(state_space.IsNull(state), false);
  EXPECT_EQ(state_space.Size(state), size);

  std::array<float, size> ps = {0.1, 0.2, 0.13, 0.12, 0.18, 0.15, 0.07, 0.05};

  for (uint64_t i = 0; i < size; ++i) {
    auto r = std::sqrt(ps[i]);
    state_space.SetAmpl(state, i, r * std::cos(i), r * std::sin(i));
  }

  auto samples = state_space.Sample(state, num_samples, 1);

  EXPECT_EQ(samples.size(), num_samples);
  std::array<double, size> bins = {0, 0, 0, 0, 0, 0, 0, 0};

  for (auto sample : samples) {
    ASSERT_LT(sample, size);
    bins[sample] += 1;
  }

  for (uint64_t i = 0; i < size; ++i) {
    EXPECT_NEAR(bins[i] / num_samples, ps[i], 4e-4);
  }
}

template <typename Simulator>
void TestSamplingCrossEntropyDifference() {
  unsigned depth = 30;
  uint64_t num_samples = 2000000;

  std::stringstream ss(circuit_string);
  Circuit<GateQSim<float>> circuit;
  EXPECT_EQ(
      CircuitQsimParser<IO>::FromStream(depth, provider, ss, circuit), true);

  using StateSpace = typename Simulator::StateSpace;
  using State = typename StateSpace::State;
  using Runner = QSimRunner<IO, BasicGateFuser<GateQSim<float>>, Simulator>;

  StateSpace state_space(circuit.num_qubits, 1);
  State state = state_space.CreateState();

  EXPECT_EQ(state_space.IsNull(state), false);

  state_space.SetStateZero(state);

  typename Runner::Parameter param;
  param.num_threads = 1;
  param.verbosity = 0;

  EXPECT_EQ(Runner::Run(param, depth, circuit, state), true);

  auto bitstrings = state_space.Sample(state, num_samples, 1);
  EXPECT_EQ(bitstrings.size(), num_samples);

  double sum = 0;
  for (uint64_t i = 0; i < num_samples; ++i) {
    double p = std::norm(state_space.GetAmpl(state, bitstrings[i]));
    sum += std::log(p);
  }

  double gamma = 0.5772156649;
  double ced = circuit.num_qubits * std::log(2) + gamma + sum / num_samples;

  EXPECT_NEAR(ced, 1.0, 2e-3);
}

}  // namespace qsim

#endif  // STATESPACE_TESTFIXTURE_H_
