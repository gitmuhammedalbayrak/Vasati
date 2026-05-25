## 2026-05-25 - [Replace std::to_string with stack-allocated buffers in string formatting]
**Learning:** In heavily called string formatting functions like `td_to_vakt` and `zaman::sat_turk_v_d()`, multiple `std::to_string` allocations and string concatenations (`+` or `.append()`) cause severe memory allocation bottlenecks. Additionally, avoiding `substr()` when passing values to `vakt_to_td()` and instead using pointer offsets (`const char* + offset`) significantly reduces temporary string allocations.
**Action:** Use manual, fixed-size stack character buffers (e.g., `char buf[]`) and direct ASCII arithmetic (`'0' + value`) combined with pointer offsets for parsing to bypass temporary object creation entirely, yielding measurable performance improvements.

## 2026-05-25 - [Replace std::to_string with stack-allocated buffers in string formatting]
**Learning:** In heavily called string formatting functions like `td_to_vakt` and `zaman::sat_turk_v_d()`, multiple `std::to_string` allocations and string concatenations (`+` or `.append()`) cause severe memory allocation bottlenecks.
**Action:** Use manual, fixed-size stack character buffers (e.g., `char buf[]`) and direct ASCII arithmetic (`'0' + value`) to bypass temporary object creation entirely, yielding measurable performance improvements.
