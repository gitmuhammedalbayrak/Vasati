## 2026-05-03 - [Optimize XML Parsing via Lazy Initialization]
**Learning:** In C++ codebases like Vasati that heavily rely on parsing large XML datasets (e.g., `Vakitler.xml` using `pugixml`), parsing the document repeatedly upon every instantiation of a core class (`zaman`) creates a massive performance bottleneck.
**Action:** Implemented lazy initialization (a `static bool is_loaded` flag along with making `pugi::xml_document` and `pugi::xml_node` static members) so that the XML document is loaded only once per program lifecycle. This simple change yields a roughly ~3x performance boost for object instantiation (from ~3.8s down to ~1.1s for 10000 object instantiations).
## 2026-05-08 - [XML Parsing Optimization]
**Learning:** Parsing the XML document in the constructor of `zaman` class without caching causes a significant performance bottleneck (around 40ms per 100 instantiations). Repeatedly loading the file creates high overhead.
**Action:** Used a C++11 method-local magic static and an immediately invoked lambda to cache the `cityinfo` XML node (`zaman::sehir`), reducing 100 instantiations from ~40ms to ~14ms.

## 2024-05-11 - [XML Lookup Optimization]
**Learning:** Repeatedly calling `pugi::xml_node::find_child_by_attribute` to look up prayer times by `dayofyear` is an O(N) linear search bottleneck that slows down `zaman` class instantiations.
**Action:** Replaced it with an O(1) array lookup. Since `dayofyear` acts as a sequential 0-based index (0-365), we can cache the `const char*` text of each `prayertimes` node into a static `cached_nodes[400]` array using a magic static block. This reduced instantiation time nearly by half.

## 2026-05-12 - [Remove Duplicate Static Initialization & Unsafe String Operations]
**Learning:** The previous optimization attempt introduced a bug where 'cached_nodes' was initialized twice as different types (one array of xml_node pointers, one array of const char*). Moreover, directly casting const char* returned from pugixml without assigning to std::string when used in ternary operations can cause operand type mismatches.
**Action:** Removed the redundant array initialization block and cast the char* obtained via `pt.text().get()` from the single cached xml_node array to `std::string` inside the ternary conditional to prevent implicit conversion mismatches.

## 2024-05-19 - [String Atama ve Formatlama ile Bellek Sızıntısı ve Format Hatalarının Giderilmesi]
**Learning:** Sık çağrılan fonksiyonlarda (örneğin `vkt_turk_v_d` ve `sat_turk_v_d`) `std::string::append()` kullanımı, nesne örnekleri veya tekrarlı metod çağrıları üzerinden durumu sıfırlamadan yapıldığında sınırsız bellek büyümesine neden olur (ör. saatin "10:35:0610:35:06" gibi büyümesi). Ayrıca, birden fazla `std::to_string` çağrısını string birleştirme ile (`+`) kullanmak hem gereksiz bellek tahsislerine yol açar hem de `1:5:9` gibi sıfır dolgusu eksik olan hatalı saat formatlarına neden olur.
**Action:** Sınıf üyeleri yeniden hesaplanırken her zaman `.append()` yerine doğrudan atama (`=`) kullanın. Sabit boyutlu string formatlamalarında `std::to_string` ve birleştirme yerine yığın (stack) üzerinde sabit boyutlu `char` buffer (ör. `char buffer[16]`) ve `std::snprintf` (ör. `"%d:%02d:%02d"`) kombinasyonunu kullanın. Bu sayede bellek tüketimi sabit kalır, gereksiz tahsisler engellenir ve sayıların doğru formatlanması garanti altına alınır.
