/**
 * -e-
 *
 * vasatî - version 0.9
 * --------------------------------------------------------
 * Copyright (C) 1439-1440, by M.M.M. Samil R.T.Ü (muhammed.samil.albayrak@outlook.com)
 *
 * This software is licensed under T1. For details, see the end of this file.
 *
 * This software utilizes the pugixml parser.
 * [Copyright (C) 2006-2018, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)]
 */

#ifndef SOURCE_ZAMAN_CPP
#define SOURCE_ZAMAN_CPP

#include "include-class/Zaman.hpp"

pugi::xml_document zaman::dosya;
pugi::xml_node zaman::sehir;

void zaman::tkvm_h_v_d()
{
	//zaman paketinin temel verileri;
	zaman::now   = time(0)         ;
	zaman::ltm   = localtime(&now) ;
	zaman::dt    = ctime(&now)     ;

	zaman::h_rakam_gun_senenin    = (1 + zaman::ltm->tm_yday)   ;
	zaman::h_rakam_gun_ayin       = zaman::ltm->tm_mday         ;
	zaman::h_rakam_gun_haftanin   = zaman::ltm->tm_wday         ;
	zaman::h_rakam_sene           = (1900 + zaman::ltm->tm_year);
	zaman::h_rakam_ay             = (1 + zaman::ltm->tm_mon)    ;
};
void zaman::tkvm_turk_v_d()
{
	zaman::rakam_gun_haftanin = zaman::h_rakam_gun_haftanin;

	{
	//hicri seneyi bulma algoritması.
	int a_rakami      = zaman::h_rakam_sene - 621              ;
	int b_rakami      = a_rakami / 33                          ;
	int c_rakami      = a_rakami + b_rakami                    ;

	zaman::rakam_sene = c_rakami                               ;
	};

	zaman::rakam_gun_ayin = 0; //bilgi boş olduğu belli olsun için
	zaman::rakam_gun_senenin = 0; //yukardaki gibi.
	zaman::rakam_ay = 0; //yukardaki gibi keza.
};

// ⚡ Bolt Optimization: Replace vakt_to_td string parameter with const char* to avoid allocations
// The input is always coming from substr or literal, we can do it directly.
unsigned int zaman::vakt_to_td(const char* p)
{
	if (!p) return 0;
	unsigned int h = 0;
	unsigned int m = 0;
	while (*p && !std::isdigit(*p)) p++;
	while (*p && std::isdigit(*p)) {
		h = h * 10 + (*p - '0');
		p++;
	}
	if (*p == ':') p++;
	while (*p && std::isdigit(*p)) {
		m = m * 10 + (*p - '0');
		p++;
	}
	return (h * 60) + m;
}

std::string zaman::td_to_vakt(unsigned int td)
{
	// ⚡ Bolt Optimization: Replace multiple std::to_string allocations and string concatenations
	// with a fast, fixed-size stack buffer and direct ASCII formatting
	char buf[6];
	unsigned int h = (td / 60) % 12;
	unsigned int m = td % 60;

	int idx = 0;
	if (h >= 10) {
		buf[idx++] = '0' + (h / 10);
		buf[idx++] = '0' + (h % 10);
	} else {
		buf[idx++] = '0' + h;
	}
	buf[idx++] = ':';
	if (m >= 10) {
		buf[idx++] = '0' + (m / 10);
		buf[idx++] = '0' + (m % 10);
	} else {
		buf[idx++] = '0' + m;
	}
	buf[idx] = '\0';

	return std::string(buf, idx);
}

void zaman::vkt_h_v_d()
{

	static bool is_loaded = false;
	zaman::dosya_adresi    = "include/XML/Vakitler.xml";
	// Performans optimizasyonu: Vakitler.xml dosyasi cok buyuk oldugu icin
	// her nesne olusturuldugunda tekrar tekrar parse edilmesini onlemek uzere
	// lazy initialization (tembel ilklendirme) yontemi kullanildi.
	if (!is_loaded) {
		zaman::dosya.load_file(  zaman::dosya_adresi  )    ;
		zaman::sehir           = dosya.child("cityinfo")   ;
		is_loaded = true;
	}

	char buffer[5];

	// ⚡ Bolt Optimization: Cache raw strings directly from static XML document
	// Avoids all O(N) searches and string allocation overhead entirely.
	static const char* cached_day_strings[400] = {nullptr};
	static const pugi::xml_node cached_sehir = []() {
		static pugi::xml_document doc;
		if (!doc.load_file("include/XML/Vakitler.xml") && !doc.load_file("vakitler.xml")) {
			throw std::runtime_error("XML load failed");
		}
		pugi::xml_node node = doc.child("cityinfo");
		if (!node) {
			throw std::runtime_error("Missing cityinfo node");
		}
		for (pugi::xml_node pt = node.child("prayertimes"); pt; pt = pt.next_sibling("prayertimes")) {
			int day = pt.attribute("dayofyear").as_int(-1);
			if (day >= 0 && day < 400) {
				cached_day_strings[day] = pt.text().get();
			}
		}
		return node;
	}();

	zaman::sehir = cached_sehir;

	int current_day = zaman::h_rakam_gun_senenin;
	zaman::xml_bu_gun = (current_day >= 0 && current_day < 400 && cached_day_strings[current_day]) ? cached_day_strings[current_day] : "";

	const char* t_str = zaman::xml_bu_gun.c_str();
	// ⚡ Bolt Optimization: Replace slow std::string::substr calls with fast pointer-based parsing
	// Avoids 14 string allocations per instantiation for vakt_to_td calls.
	zaman::h_aksam_td             = vakt_to_td(t_str + 50);
	zaman::h_istibak_nucum_td     = vakt_to_td(t_str + 56);
	zaman::h_yatsi_td             = vakt_to_td(t_str + 62);
	zaman::h_isa_sani_td          = vakt_to_td(t_str + 68);

	// We still set string variables to keep API compatible
	zaman::h_aksam         = zaman::xml_bu_gun.substr(50, 6);
	zaman::h_istibak_nucum = zaman::xml_bu_gun.substr(56, 6);
	zaman::h_yatsi         = zaman::xml_bu_gun.substr(62, 6);
	zaman::h_isa_sani      = zaman::xml_bu_gun.substr(68, 6);

	//buradaka kodları yeniliyoruz çünkü bir sonraki gün kılacağız verileri:

	int next_day = zaman::h_rakam_gun_senenin + 1;
	zaman::xml_bu_gun = (next_day >= 0 && next_day < 400 && cached_day_strings[next_day]) ? cached_day_strings[next_day] : "";
	t_str = zaman::xml_bu_gun.c_str();

	zaman::h_imsak_td             = vakt_to_td(t_str + 0);
	zaman::h_sabah_td             = vakt_to_td(t_str + 5);
	zaman::h_gunes_td             = vakt_to_td(t_str + 10);
	zaman::h_israk_td             = vakt_to_td(t_str + 15);
	zaman::h_kerahet_td           = vakt_to_td(t_str + 20);
	zaman::h_ogle_td              = vakt_to_td(t_str + 26);
	zaman::h_ikindi_td            = vakt_to_td(t_str + 32);
	zaman::h_asr_sani_td          = vakt_to_td(t_str + 38);
	zaman::h_isfirar_sems_td      = vakt_to_td(t_str + 44);
	zaman::h_kible_saati_td       = vakt_to_td(t_str + 74);

	zaman::h_imsak          = zaman::xml_bu_gun.substr(0, 4) ;
	zaman::h_sabah          = zaman::xml_bu_gun.substr(5, 5) ;
	zaman::h_gunes          = zaman::xml_bu_gun.substr(10, 5);
	zaman::h_israk          = zaman::xml_bu_gun.substr(15, 5);
	zaman::h_kerahet        = zaman::xml_bu_gun.substr(20, 6);
	zaman::h_ogle           = zaman::xml_bu_gun.substr(26, 6);
	zaman::h_ikindi         = zaman::xml_bu_gun.substr(32, 6);
	zaman::h_asr_sani       = zaman::xml_bu_gun.substr(38, 6);
	zaman::h_isfirar_sems   = zaman::xml_bu_gun.substr(44, 6);
	zaman::h_kible_saati    = zaman::xml_bu_gun.substr(74, 6);

};
void zaman::vkt_turk_v_d()
{
	zaman::aksam_td         = 0;
	zaman::istibak_nucum_td = zaman::h_istibak_nucum_td  - zaman::h_aksam_td        ;
	zaman::yatsi_td         = zaman::h_yatsi_td          - zaman::h_aksam_td        ;
	zaman::isa_sani_td      = zaman::h_isa_sani_td       - zaman::h_aksam_td        ;
	zaman::imsak_td         = (1440 - zaman::h_aksam_td) + zaman::h_imsak_td        ; //1440 bir günün toplam dakikası
	zaman::sabah_td         = (1440 - zaman::h_aksam_td) + zaman::h_sabah_td        ;
	zaman::gunes_td         = (1440 - zaman::h_aksam_td) + zaman::h_gunes_td        ;
	zaman::israk_td         = (1440 - zaman::h_aksam_td) + zaman::h_israk_td        ;
	zaman::kerahet_td       = (1440 - zaman::h_aksam_td) + zaman::h_kerahet_td      ;
	zaman::ogle_td          = (1440 - zaman::h_aksam_td) + zaman::h_ogle_td         ;
	zaman::ikindi_td        = (1440 - zaman::h_aksam_td) + zaman::h_ikindi_td       ;
	zaman::asr_sani_td      = (1440 - zaman::h_aksam_td) + zaman::h_asr_sani_td     ;
	zaman::isfirar_sems_td  = (1440 - zaman::h_aksam_td) + zaman::h_isfirar_sems_td ;
	zaman::kible_saati_td   = (1440 - zaman::h_aksam_td) + zaman::h_kible_saati_td  ;

	zaman::aksam = "00:00";
	zaman::istibak_nucum = td_to_vakt(istibak_nucum_td) ;
	zaman::yatsi         = td_to_vakt(yatsi_td)         ;
	zaman::isa_sani      = td_to_vakt(isa_sani_td)      ;
	zaman::imsak         = td_to_vakt(imsak_td)         ;
	zaman::sabah         = td_to_vakt(sabah_td)         ;
	zaman::gunes         = td_to_vakt(gunes_td)         ;
	zaman::israk         = td_to_vakt(israk_td)         ;
	zaman::kerahet       = td_to_vakt(kerahet_td)       ;
	zaman::ogle          = td_to_vakt(ogle_td)          ;
	zaman::ikindi        = td_to_vakt(ikindi_td)        ;
	zaman::asr_sani      = td_to_vakt(asr_sani_td)      ;
	zaman::isfirar_sems  = td_to_vakt(isfirar_sems_td)  ;
	zaman::kible_saati   = td_to_vakt(kible_saati_td)   ;

};

void zaman::sat_h_v_d()
{
	zaman::h_saat   = zaman::ltm->tm_hour;
	zaman::h_dakika = zaman::ltm->tm_min ;
	zaman::h_saniye = zaman::ltm->tm_sec ;
};
void zaman::sat_turk_v_d()
{
	zaman::h_zaman_td  = ((zaman::h_saat * 60) * 60)      + (zaman::h_dakika * 60) + zaman::h_saniye;
	zaman::zaman_td    = ((1440 - zaman::h_aksam_td) * 60) + zaman::h_zaman_td                      ;

	zaman::saat      =  int((( zaman::zaman_td   / 60) / 60 ) % 12);
	zaman::dakika    =  int((  zaman::zaman_td   / 60) % 60 )      ;
	zaman::saniye    =  int((  zaman::zaman_td ) % 60)             ;

	// ⚡ Bolt Optimization: Replace std::to_string allocations with fast fixed-size buffer
	char buf[9];
	int idx = 0;
	if (zaman::saat >= 10) { buf[idx++] = '0' + (zaman::saat / 10); buf[idx++] = '0' + (zaman::saat % 10); } else { buf[idx++] = '0' + zaman::saat; }
	buf[idx++] = ':';
	if (zaman::dakika >= 10) { buf[idx++] = '0' + (zaman::dakika / 10); buf[idx++] = '0' + (zaman::dakika % 10); } else { buf[idx++] = '0' + zaman::dakika; }
	buf[idx++] = ':';
	if (zaman::saniye >= 10) { buf[idx++] = '0' + (zaman::saniye / 10); buf[idx++] = '0' + (zaman::saniye % 10); } else { buf[idx++] = '0' + zaman::saniye; }
	buf[idx] = '\0';
	zaman::simdiki_zaman_turk = std::string(buf, idx);

};




void zaman::h_v_d()
{
	tkvm_h_v_d()     ;
	vkt_h_v_d ()     ;
	sat_h_v_d ()     ;
};
void zaman::turk_v_d()
{
	tkvm_turk_v_d()     ;
	vkt_turk_v_d ()     ;
	sat_turk_v_d ()     ;
};



void zaman::gos_turk_v()
{
	std::cout << "__TURK__            Topluca   : " << "" << std::endl << std::endl;

	std::cout << "__TURK__            Sene      : " << zaman::rakam_sene          << std::endl;
	std::cout << "__TURK__            Ay        : " << zaman::rakam_ay            << ". ay"   << std::endl;
	std::cout << "__TURK__ (Yilin)    Gun       : " << zaman::rakam_gun_senenin   << ". gunu" << std::endl;
	std::cout << "__TURK__ (Ayin)     Gun       : " << zaman::rakam_gun_ayin      << ". gunu" << std::endl;
	std::cout << "__TURK__ (Haftanin) Gun       : " << zaman::rakam_gun_haftanin  << ". gunu" << std::endl << std::endl;

	std::cout << "__TURK__ saat ve dakika       : " << zaman::simdiki_zaman_turk   << std::endl;
	std::cout << "__TURK__ Saat                 : " << zaman::saat                 << std::endl;
	std::cout << "__TURK__ Dakika               : " << zaman::dakika               << std::endl;
	std::cout << "__TURK__ Saniye               : " << zaman::saniye               << std::endl << std::endl;

	std::cout << "__TURK__ aksam                : " << zaman::aksam         << std::endl;
	std::cout << "__TURK__ istibak-i nucum      : " << zaman::istibak_nucum << std::endl;
	std::cout << "__TURK__ yatsi (isa-i evvel)  : " << zaman::yatsi         << std::endl;
	std::cout << "__TURK__ isa-i sani           : " << zaman::isa_sani      << std::endl;
	std::cout << "__TURK__ imsak                : " << zaman::imsak         << std::endl;
	std::cout << "__TURK__ sabah                : " << zaman::sabah         << std::endl;
	std::cout << "__TURK__ gunes                : " << zaman::gunes         << std::endl;
	std::cout << "__TURK__ israk                : " << zaman::israk         << std::endl;
	std::cout << "__TURK__ kerahet              : " << zaman::kerahet       << std::endl;
	std::cout << "__TURK__ ogle                 : " << zaman::ogle          << std::endl;
	std::cout << "__TURK__ ikindi               : " << zaman::ikindi        << std::endl;
	std::cout << "__TURK__ asr-i sani           : " << zaman::asr_sani      << std::endl;
	std::cout << "__TURK__ isfirar-i sems       : " << zaman::isfirar_sems  << std::endl;
	std::cout << "__TURK__ kible saati          : " << zaman::kible_saati   << std::endl;

	std::cout << std::endl;
};
void zaman::gos_h_v()
{
	std::cout << std::endl << std::endl << std::endl << std::endl;

	std::cout << "(hrist) (ing)      Topluca    : " << zaman::dt                   << std::endl ;

	std::cout << "(hrist)            Sene       : " << zaman::h_rakam_sene         << std::endl ;
	std::cout << "(hrist)            Ay         : " << zaman::h_rakam_ay           << ". ay"   << std::endl;
	std::cout << "(hrist) (Yilin)    Gun        : " << zaman::h_rakam_gun_senenin  << ". gunu" << std::endl;
	std::cout << "(hrist) (Ayin)     Gun        : " << zaman::h_rakam_gun_ayin     << ". gunu" << std::endl;
	std::cout << "(hrist) (Haftanin) Gun        : " << zaman::h_rakam_gun_haftanin << ". gunu" << std::endl << std::endl;

	std::cout << "(hrist) Saat                  : " << zaman::h_saat          << std::endl;
	std::cout << "(hrist) Dakika                : " << zaman::h_dakika        << std::endl;
	std::cout << "(hrist) Saniye                : " << zaman::h_saniye        << std::endl << std::endl;

	std::cout << "(hrist) aksam                 : " << zaman::h_aksam         << std::endl;
	std::cout << "(hrist) istibak-i nucum       : " << zaman::h_istibak_nucum << std::endl;
	std::cout << "(hrist) yatsi (isa-i evvel)   : " << zaman::h_yatsi         << std::endl;
	std::cout << "(hrist) isa-i sani            : " << zaman::h_isa_sani      << std::endl;
	std::cout << "(hrist) imsak                 : " << zaman::h_imsak         << std::endl;
	std::cout << "(hrist) sabah                 : " << zaman::h_sabah         << std::endl;
	std::cout << "(hrist) gunes                 : " << zaman::h_gunes         << std::endl;
	std::cout << "(hrist) israk                 : " << zaman::h_israk         << std::endl;
	std::cout << "(hrist) kerahet               : " << zaman::h_kerahet       << std::endl;
	std::cout << "(hrist) ogle                  : " << zaman::h_ogle          << std::endl;
	std::cout << "(hrist) ikindi                : " << zaman::h_ikindi        << std::endl;
	std::cout << "(hrist) asr-i sani            : " << zaman::h_asr_sani      << std::endl;
	std::cout << "(hrist) isfirar-i sems        : " << zaman::h_isfirar_sems  << std::endl;
	std::cout << "(hrist) kible saati           : " << zaman::h_kible_saati   << std::endl;
};

zaman::zaman()
{
	h_v_d();
	turk_v_d();

	gos_turk_v();
	gos_h_v();
}
zaman::~zaman()
{
}

#endif

/**
 * Copyright (C) 1439-1440, by M.M.M. Samil R.T.Ü (muhammed.samil.albayrak@outlook.com)
 *
 * T1 License Details:
 *
 * Redistribution and usage require notification to the developer.
 * Unauthorized use and development are prohibited. Rights may be revoked
 * if any hostility against Turkey is identified. This license and its
 * terms must be cited without omission in any redistributed or derivative
 * works. The code cannot be sold or used for commercial profit.
 *
 * -e-
 */
