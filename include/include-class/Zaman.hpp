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

class zaman
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
	std::string isim_ay;
	//------------------------------------------------------------------------------
	unsigned int rakam_gun_senenin;
	unsigned int rakam_gun_ayin;
	unsigned int rakam_gun_haftanin;
	//------------------------------------------------------------------------------
	unsigned int rakam_ay;
	unsigned int rakam_sene;
	//------------------------------------------------------------------------------
	std::string h_isim_ay;
	//------------------------------------------------------------------------------
	unsigned int h_rakam_gun_senenin;
	unsigned int h_rakam_gun_ayin;
	unsigned int h_rakam_gun_haftanin;
	//------------------------------------------------------------------------------
	unsigned int h_rakam_ay;
	unsigned int h_rakam_sene;

	//------------------------------------------------------------------------------
	//ASAGIDAKI DEGISKENLER SAATLE ILISKILIDIR;
	//------------------------------------------------------------------------------
	unsigned int saat;
	unsigned int dakika;
	unsigned int saniye;
	//------------------------------------------------------------------------------
	unsigned int h_saat;
	unsigned int h_dakika;
	unsigned int h_saniye;
	//------------------------------------------------------------------------------
	std::string h_imsak; //h hrist demek. Yani hristiyan saatine göre vakitler.
	std::string h_sabah;
	std::string h_gunes;
	std::string h_israk;
	std::string h_kerahet;
	std::string h_ogle;
	std::string h_ikindi;
	std::string h_asr_sani;
	std::string h_isfirar_sems;
	std::string h_aksam;
	std::string h_istibak_nucum;
	std::string h_yatsi;
	std::string h_isa_sani;
	std::string h_kible_saati;

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

	////////VAKİTLER İÇİN TOPLAM DAKİKA LEFTVALUE'LARI.////////

	unsigned int h_aksam_td          ; //td toplam dakika demek.
	unsigned int h_istibak_nucum_td  ;
	unsigned int h_yatsi_td          ;
	unsigned int h_isa_sani_td       ;
	unsigned int h_imsak_td          ;
	unsigned int h_sabah_td          ;
	unsigned int h_gunes_td          ;
	unsigned int h_israk_td          ;
	unsigned int h_kerahet_td        ;
	unsigned int h_ogle_td           ;
	unsigned int h_ikindi_td         ;
	unsigned int h_asr_sani_td       ;
	unsigned int h_isfirar_sems_td   ;
	unsigned int h_kible_saati_td    ;

	unsigned int aksam_td          ;
	unsigned int istibak_nucum_td  ;
	unsigned int yatsi_td          ;
	unsigned int isa_sani_td       ;
	unsigned int imsak_td          ;
	unsigned int sabah_td          ;
	unsigned int gunes_td          ;
	unsigned int israk_td          ;
	unsigned int kerahet_td        ;
	unsigned int ogle_td           ;
	unsigned int ikindi_td         ;
	unsigned int asr_sani_td       ;
	unsigned int isfirar_sems_td   ;
	unsigned int kible_saati_td    ;
	
	unsigned int h_zaman_td      ;
	unsigned int zaman_td        ;

	/////////////////////////////FONKSIYONLAR///////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	void h_v_d()    ;
	void turk_v_d() ;
	
	void tkvm_h_v_d()    ;
	void tkvm_turk_v_d() ;

	void vkt_h_v_d()         ;
	void vkt_turk_v_d()      ;

	void sat_h_v_d()    ;
	void sat_turk_v_d() ;

	void gos_turk_v() ;
	void gos_h_v()    ;

	zaman() ;
	~zaman();
};
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
