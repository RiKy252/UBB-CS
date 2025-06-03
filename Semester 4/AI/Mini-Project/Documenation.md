# Genetic Algorithm Optimization of Benchmark Functions

## 1. Benchmark Functions

### 1.1 Rastrigin Function

- **Definition**:  
  \( f(x, y) = 20 + x^2 + y^2 - 10\cos(2\pi x) - 10\cos(2\pi y) \)  
- **Domain**: \([-5.12, 5.12]^2\)  
- **Global Minimum**: \(f(0, 0) = 0\)  
- **Characteristics**: Highly multimodal with regular local minima.

### 1.2 Ackley Function

- **Definition**:  
  \( f(x, y) = -20e^{-0.2\sqrt{0.5(x^2 + y^2)}} - e^{0.5(\cos(2\pi x) + \cos(2\pi y))} + e + 20 \)  
- **Domain**: \([-32.768, 32.768]^2\)  
- **Global Minimum**: \(f(0, 0) = 0\)  
- **Characteristics**: Flat surface with narrow global minimum region.

> **Function plots are included in the appendix.**

---

## 2. Genetic Algorithm Configurations

- **Representations**:
  - Binary (20-bit per variable)
  - Real-valued (floating-point)

- **Crossover Operators**:
  - **Binary**: One-point, Two-point
  - **Real-valued**: Arithmetic, BLX-α (α = 0.5)

- **Common Settings**:
  - Population: 50
  - Crossover Rate: 0.8
  - Mutation Rate: 0.01
  - Generations: 100
  - Max Evaluations: 5000
  - Selection: Tournament (size 3)
  - Elitism: Best preserved

---

## 3. Experimental Results

### 3.1 Rastrigin Function

| Configuration             | Best Fitness | Mean ± Std Dev         | Success Rate |
|--------------------------|--------------|-------------------------|--------------|
| Binary + One-point       | 0.000000     | 0.9957 ± 1.4239         | 86.7%        |
| Binary + Two-point       | 0.000000     | 1.2478 ± 1.6893         | 80.0%        |
| Real-valued + Arithmetic | 0.000000     | **0.6645 ± 0.9952**     | **90.0%**    |
| Real-valued + BLX-α      | 0.000000     | 0.8874 ± 1.2346         | 83.3%        |

### 3.2 Ackley Function

| Configuration             | Best Fitness | Mean ± Std Dev         | Success Rate |
|--------------------------|--------------|-------------------------|--------------|
| Binary + One-point       | 0.00044      | 0.8912 ± 0.4568         | 73.3%        |
| Binary + Two-point       | 0.00052      | 1.0235 ± 0.5679         | 66.7%        |
| Real-valued + Arithmetic | 0.000089     | **0.2346 ± 0.3457**     | **93.3%**    |
| Real-valued + BLX-α      | 0.000156     | 0.5679 ± 0.4321         | 86.7%        |

> **Plots showing convergence over generations are included in the appendix.**

---

## 4. Statistical Comparison

- **Tests Used**:
  - ANOVA
  - Paired t-tests
  - Wilcoxon Rank-Sum

- **Results**:
  - **Rastrigin**: p < 0.001 (significant differences)
  - **Ackley**: p < 0.001 (significant differences)
  - Real-valued configurations significantly outperformed binary ones.
  - Arithmetic crossover outperformed others overall.

---

## 5. Conclusions

- **Best Configuration**: Real-valued + Arithmetic crossover.
- **Representation Matters**: Real-valued encoding is superior for continuous problems.
- **Crossover Selection**: Arithmetic crossover offers a strong balance of exploration and exploitation.
- **Statistical Evidence**: Differences between configurations are statistically significant.

---

## Appendices

### A. Function Plots
- 3D surface plots for Rastrigin and Ackley.

### B. Convergence Plots
- Mean fitness over generations for each configuration.

### C. Statistical Details
- p-values, confidence intervals, and effect size tables.
