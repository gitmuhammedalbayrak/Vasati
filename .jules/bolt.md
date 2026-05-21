## 2026-05-03 - [Optimize XML Parsing via Lazy Initialization]
**Learning:** In C++ codebases like Vasati that heavily rely on parsing large XML datasets (e.g., `Vakitler.xml` using `pugixml`), parsing the document repeatedly upon every instantiation of a core class (`zaman`) creates a massive performance bottleneck.
**Action:** Implemented lazy initialization (a `static bool is_loaded` flag along with making `pugi::xml_document` and `pugi::xml_node` static members) so that the XML document is loaded only once per program lifecycle. This simple change yields a roughly ~3x performance boost for object instantiation (from ~3.8s down to ~1.1s for 10000 object instantiations).
## 2026-05-08 - [XML Parsing Optimization]
**Learning:** Parsing the XML document in the constructor of `zaman` class without caching causes a significant performance bottleneck (around 40ms per 100 instantiations). Repeatedly loading the file creates high overhead.
**Action:** Used a C++11 method-local magic static and an immediately invoked lambda to cache the `cityinfo` XML node (`zaman::sehir`), reducing 100 instantiations from ~40ms to ~14ms.

## 2024-05-11 - [XML Lookup Optimization]
**Learning:** Repeatedly calling `pugi::xml_node::find_child_by_attribute` to look up prayer times by `dayofyear` is an O(N) linear search bottleneck that slows down `zaman` class instantiations.
**Action:** Replaced it with an O(1) array lookup. Since `dayofyear` acts as a sequential 0-based index (0-365), we can cache the `const char*` text of each `prayertimes` node into a static `cached_nodes[400]` array using a magic static block. This reduced instantiation time nearly by half.

## 2026-05-21 - [O(1) XML Metin Önbellekleme]
**Learning:** pugixml kullanırken düğümleri (pugi::xml_node) önbelleğe almak veya sürekli `find_child_by_attribute` ile O(N) arama yapmak (yaklaşık 100k iterasyonda 8.6s) ciddi bir darboğazdır. `pugi::xml_node` nesneleri değer olarak döndürüldüğünde veya statik yaşam döngüsüne sahip olmayan yerel düğüm referansları tutulduğunda bellek/kapsam sorunları veya derleme hataları oluşabilir.
**Action:** C++'ta pugixml okumalarını optimize ederken statik bir `pugi::xml_document` içerisindeki metin alanlarının DOĞRUDAN pointer'larını (`pt.text().get()`) `static const char* cached_strings[400]` dizisi ile gün değerine göre map'le. Bu, O(N) armayı O(1)'e düşürür ve kopyalama/atama maliyetlerini yok ederek çalışma hızını ~6.4 kat (1.3s) artırır.
