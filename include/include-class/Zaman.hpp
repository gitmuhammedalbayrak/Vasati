/**
 * bismillahirrahmanirrahim
 *
 * vasatî - version 0.9
 * --------------------------------------------------------
 * Copyright (C) 1439-1440, by Üsküdarlı Fikret oğlu Muhammed Şamil (muhammed.garib@gmail.com)
 *
 * Bu yazılım T1 ile lisanlanmıştır, ayrıntıları için sayfa sonuna bakınız
 *
 * Bu yazılım sağlanırken pugixml parser'dan faidelenilmiştir.
 * [Copyright (C) 2006-2018, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)]
 */

#ifndef HEADER_ZAMAN_HPP
#define HEADER_ZAMAN_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "packages/pugixml-1.9/src/pugixml.hpp"

class Zaman
{
public:
	//------------------------------------------------------------------------------
	//ASAGIDAKI DEGISKENLER DOSYA ISLEMLERIYLE ILISKILIDIR;
	//------------------------------------------------------------------------------
	pugi::xml_document dosya;
	const char* dosya_adresi;
	const char* bu_gun_const;
	pugi::xml_node sehir;
	std::string bu_gun_deger;
	std::string xml_bu_gun;

	//------------------------------------------------------------------------------
	//ASAGIDAKI DEGISKENLER ZAMAN PAKETININ TEMEL VERILERIYLE ILISKILIDIR;
	//------------------------------------------------------------------------------
	time_t now;
	tm *ltm;
	char* dt;

	//------------------------------------------------------------------------------
	//ASAGIDAKI DEGISKENLER TAKVIMLE ILISKILIDIR;
	//------------------------------------------------------------------------------
	std::string isim_gun;
	std::string isim_ay;
	std::string isim_vakit;
	//------------------------------------------------------------------------------
	unsigned int rakam_gun_senenin;
	unsigned int rakam_gun_ayin;
	unsigned int rakam_gun_haftanin;
	//------------------------------------------------------------------------------
	unsigned int rakam_ay;
	unsigned int rakam_sene;
	//------------------------------------------------------------------------------
	std::string hrist_isim_ay;
	//------------------------------------------------------------------------------
	unsigned int hrist_rakam_gun_senenin;
	unsigned int hrist_rakam_gun_ayin;
	unsigned int hrist_rakam_gun_haftanin;
	//------------------------------------------------------------------------------
	unsigned int hrist_rakam_ay;
	unsigned int hrist_rakam_sene;

	//------------------------------------------------------------------------------
	//ASAGIDAKI DEGISKENLER SAATLE ILISKILIDIR;
	//------------------------------------------------------------------------------
	unsigned int saat;
	unsigned int dakika;
	unsigned int saniye;
	//------------------------------------------------------------------------------
	unsigned int hrist_saat;
	unsigned int hrist_dakika;
	unsigned int hrist_saniye;
	//------------------------------------------------------------------------------
	std::string b_h_imsak; //herhalde bu b_h bi'l-hristî demek :)
	std::string b_h_sabah;
	std::string b_h_gunes;
	std::string b_h_israk;
	std::string b_h_kerahet;
	std::string b_h_ogle;
	std::string b_h_ikindi;
	std::string b_h_asr_sani;
	std::string b_h_isfirar_sems;
	std::string b_h_aksam;
	std::string b_h_istibak_nucum;
	std::string b_h_yatsi;
	std::string b_h_isa_sani;
	std::string b_h_kible_saati;

	std::string aksam;
	std::string istibak_nucum;
	std::string yatsi;
	std::string isa_sani;
	std::string imsak;
	std::string sabah;
	std::string gunes;
	std::string israk;
	std::string kerahet;
	std::string ogle;
	std::string ikindi;
	std::string asr_sani;
	std::string isfirar_sems;
	std::string kible_saati;

	std::string simdiki_zaman_turk;

	/////////////////////////////FONKSIYONLAR///////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	void takvim_v_d();
	void vakit_v_d();
	void saat_v_d();

	void tkvm_hrist_v_d();
	void tkvm_turk_v_d();

	void vkt_karisik_gecici();
	void vkt_hrist_v_d();
	void vkt_turk_v_d();

	void sat_hrist_v_d();
	void sat_turk_v_d();

	void gos_turk_v();
	void gos_hrist_v();

	Zaman();
	~Zaman();
};
#endif

#if defined(ZAMAN_HEADER_ONLY) && !defined(ZAMAN_SOURCE)
#	define ZAMAN_SOURCE "pugixml.cpp"
#	include ZAMAN_SOURCE
#endif

/**

 * Copyright (C) 1439-1440, by Üsküdarlı Fikret oğlu Muhammed Şamil (muhammed.garib@gmail.com)
 *
 * T1 Lisansı ayrıntıları:
 *
 * Dağıtımı ve kullanımında geliştiricisine haber verilmek kaydı
 * bulunmaktadır. Gayr-ı müslimler izn dışında kullanamaz ve
 * geliştiremezler. Türk düşmanlığı tesbit edilen kullanıcı ve
 * geliştiricilerin verilmişse hakları iptal edilir. İş bu lisans
 * maddeleri, kodları devr alan taraflarca, devralınan yerde
 * eksiksiz zikredilmelidir. Para ile satılamaz ticari gelir elde
 * etmeye aracı tutulamazlar.
 *
 * et-tevfik billah
 * ve'l-hamdu-lillahi rabbilalemin.
 **/
