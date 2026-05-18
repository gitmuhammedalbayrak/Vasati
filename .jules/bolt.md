## 2026-05-03 - [Optimize XML Parsing via Lazy Initialization]
**Learning:** In C++ codebases like Vasati that heavily rely on parsing large XML datasets (e.g., `Vakitler.xml` using `pugixml`), parsing the document repeatedly upon every instantiation of a core class (`zaman`) creates a massive performance bottleneck.
**Action:** Implemented lazy initialization (a `static bool is_loaded` flag along with making `pugi::xml_document` and `pugi::xml_node` static members) so that the XML document is loaded only once per program lifecycle. This simple change yields a roughly ~3x performance boost for object instantiation (from ~3.8s down to ~1.1s for 10000 object instantiations).
## 2026-05-08 - [XML Parsing Optimization]
**Learning:** Parsing the XML document in the constructor of `zaman` class without caching causes a significant performance bottleneck (around 40ms per 100 instantiations). Repeatedly loading the file creates high overhead.
**Action:** Used a C++11 method-local magic static and an immediately invoked lambda to cache the `cityinfo` XML node (`zaman::sehir`), reducing 100 instantiations from ~40ms to ~14ms.

## 2024-05-11 - [XML Lookup Optimization]
**Learning:** Repeatedly calling `pugi::xml_node::find_child_by_attribute` to look up prayer times by `dayofyear` is an O(N) linear search bottleneck that slows down `zaman` class instantiations.
**Action:** Replaced it with an O(1) array lookup. Since `dayofyear` acts as a sequential 0-based index (0-365), we can cache the `const char*` text of each `prayertimes` node into a static `cached_nodes[400]` array using a magic static block. This reduced instantiation time nearly by half.

## 2026-05-18 - [String Formatting Optimization in Zaman Class]
**Learning:** In heavily called string formatting functions like `td_to_vakt` which is used extensively to construct time strings during `zaman` class instantiation, relying on `std::to_string()` and string concatenation via the `+` operator causes severe memory allocation bottlenecks due to the creation of multiple temporary string objects.
**Action:** Replaced `std::to_string()` and the `+` operator with a manual, fixed-size stack character buffer (`char buf[6]`) and direct ASCII arithmetic (`'0' + value`). This simple low-level optimization completely eliminates the temporary allocations and yields a roughly ~4x performance improvement for formatting operations.
