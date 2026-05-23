## 2024-05-24 - `zaman::td_to_vakt` and String Allocation Optimization
**Learning:** In C++, frequently called formatting functions like `td_to_vakt` and `zaman::sat_turk_v_d` that use multiple `std::to_string` allocations and string concatenations (`+` or `.append()`) suffer from high memory allocation overhead, creating severe memory and CPU bottlenecks.
**Action:** Replace dynamic allocations inside highly-called utility functions with manual, fixed-size stack buffers (`char buf[]`) and direct ASCII arithmetic (`'0' + value`) to entirely bypass temporary string objects. This reduces execution time significantly in string formatting benchmarks.

## 2024-05-24 - `zaman::td_to_vakt` and String Allocation Optimization
**Learning:** In C++, frequently called formatting functions like `td_to_vakt` and `zaman::sat_turk_v_d` that use multiple `std::to_string` allocations and string concatenations (`+` or `.append()`) suffer from high memory allocation overhead, creating severe memory and CPU bottlenecks.
**Action:** Replace dynamic allocations inside highly-called utility functions with manual, fixed-size stack buffers (`char buf[]`) and direct ASCII arithmetic (`'0' + value`) to entirely bypass temporary string objects. This reduces execution time significantly in string formatting benchmarks.
