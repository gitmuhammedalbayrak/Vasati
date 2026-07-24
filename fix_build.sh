cat src/src-class/Zaman.cpp | sed -n '1,112p' > temp.cpp
cat << 'CHUNK' >> temp.cpp
	zaman::xml_bu_gun = (zaman::h_rakam_gun_senenin >= 0 && zaman::h_rakam_gun_senenin < 400 && cached_nodes[zaman::h_rakam_gun_senenin]) ? std::string(cached_nodes[zaman::h_rakam_gun_senenin].text().get()) : "";

	zaman::h_aksam         = zaman::xml_bu_gun.substr(50, 6);
	zaman::h_istibak_nucum = zaman::xml_bu_gun.substr(56, 6);
	zaman::h_yatsi         = zaman::xml_bu_gun.substr(62, 6);
	zaman::h_isa_sani      = zaman::xml_bu_gun.substr(68, 6);

	//buradaka kodları yeniliyoruz çünkü bir sonraki gün kılacağız verileri:

	int next_day = zaman::h_rakam_gun_senenin + 1;
	zaman::xml_bu_gun = (next_day >= 0 && next_day < 400 && cached_nodes[next_day]) ? std::string(cached_nodes[next_day].text().get()) : "";
CHUNK
cat src/src-class/Zaman.cpp | sed -n '135,$p' >> temp.cpp
mv temp.cpp src/src-class/Zaman.cpp
