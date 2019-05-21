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

#ifndef SOURCE_ZAMAN_CPP
#define SOURCE_ZAMAN_CPP

#include "include-class/zaman.hpp"

void zaman::tkvm_hrist_v_d()
{
	//zaman paketinin temel verileri;
	zaman::now   = time(0)         ;
	zaman::ltm   = localtime(&now) ;
	zaman::dt    = ctime(&now)     ;

	zaman::hrist_rakam_gun_senenin    = (1 + zaman::ltm->tm_yday)   ;
	zaman::hrist_rakam_gun_ayin       = zaman::ltm->tm_mday         ;
	zaman::hrist_rakam_gun_haftanin   = zaman::ltm->tm_wday         ;
	zaman::hrist_rakam_sene           = (1900 + zaman::ltm->tm_year);
	zaman::hrist_rakam_ay             = (1 + zaman::ltm->tm_mon)    ;
};
void zaman::tkvm_turk_v_d()
{
	zaman::rakam_gun_haftanin = zaman::hrist_rakam_gun_haftanin;

	int a_rakami      = zaman::hrist_rakam_sene - 621 ;
	int b_rakami      = a_rakami / 33                 ;
	int c_rakami      = a_rakami + b_rakami           ;

	zaman::rakam_sene = c_rakami;
};

void zaman::vkt_karisik_gecici()
{

	zaman::dosya_adresi = "include/XML/Vakitler.xml";
	zaman::dosya.load_file(  zaman::dosya_adresi  ) ;
	zaman::sehir           = dosya.child("cityinfo");




	char buffer[5];
	std::sprintf             (buffer, "%d", zaman::hrist_rakam_gun_senenin);
	const char *h_r_g_s_c_c  = buffer; //şu kısaltmaların açıklamasına dikkat etmeliyim: mesela buradaki sın iki c harfinin anlamını unutmuşum ne köt.

	zaman::xml_bu_gun        = zaman::sehir.find_child_by_attribute("prayertimes", "dayofyear", h_r_g_s_c_c).text().get();

	zaman::b_h_aksam         = zaman::xml_bu_gun.substr(50, 6);
	zaman::b_h_istibak_nucum = zaman::xml_bu_gun.substr(56, 6);
	zaman::b_h_yatsi         = zaman::xml_bu_gun.substr(62, 6);
	zaman::b_h_isa_sani      = zaman::xml_bu_gun.substr(68, 6);

	//buradaka kodları yeniliyoruz çünkü bir sonraki gün kılacağız verileri:

	std::sprintf              (buffer, "%d", (zaman::hrist_rakam_gun_senenin + 1));

	zaman::xml_bu_gun         = zaman::sehir.find_child_by_attribute("prayertimes", "dayofyear", h_r_g_s_c_c).text().get();

	zaman::b_h_imsak          = zaman::xml_bu_gun.substr(0, 4) ;
	zaman::b_h_sabah          = zaman::xml_bu_gun.substr(5, 5) ;
	zaman::b_h_gunes          = zaman::xml_bu_gun.substr(10, 5);
	zaman::b_h_israk          = zaman::xml_bu_gun.substr(15, 5);
	zaman::b_h_kerahet        = zaman::xml_bu_gun.substr(20, 6);
	zaman::b_h_ogle           = zaman::xml_bu_gun.substr(26, 6);
	zaman::b_h_ikindi         = zaman::xml_bu_gun.substr(32, 6);
	zaman::b_h_asr_sani       = zaman::xml_bu_gun.substr(38, 6);
	zaman::b_h_isfirar_sems   = zaman::xml_bu_gun.substr(44, 6);
	zaman::b_h_kible_saati    = zaman::xml_bu_gun.substr(74, 6);

	// şimdi vakitlerin dakika hesabı yapılacak yekunü alınacak ve üzerinden işlem yapılacak.

	//td : toplam dakika (aşağıdaki kısaltmalar)

	int b_h_aksam_td             = (std::stoi(b_h_aksam.substr(0, 2)) * 60)         + (std::stoi(b_h_aksam.substr(3, 5)))        ;
	int b_h_istibak_nucum_td     = (std::stoi(b_h_istibak_nucum.substr(0, 2)) * 60) + (std::stoi(b_h_istibak_nucum.substr(3, 5)));
	int b_h_yatsi_td             = (std::stoi(b_h_yatsi.substr(0, 2)) * 60)         + (std::stoi(b_h_yatsi.substr(3, 5)))        ;
	int b_h_isa_sani_td          = (std::stoi(b_h_isa_sani.substr(0, 2)) * 60)      + (std::stoi(b_h_isa_sani.substr(3, 5)))     ;
	int b_h_imsak_td             = (std::stoi(b_h_imsak.substr(0, 2)) * 60)         + (std::stoi(b_h_imsak.substr(2, 5)))        ;
	int b_h_sabah_td             = (std::stoi(b_h_sabah.substr(0, 2)) * 60)         + (std::stoi(b_h_sabah.substr(2, 5)))        ;
	int b_h_gunes_td             = (std::stoi(b_h_gunes.substr(0, 2)) * 60)         + (std::stoi(b_h_gunes.substr(2, 5)))        ;
	int b_h_israk_td             = (std::stoi(b_h_israk.substr(0, 2)) * 60)         + (std::stoi(b_h_israk.substr(2, 5)))        ;
	int b_h_kerahet_td           = (std::stoi(b_h_kerahet.substr(0, 2)) * 60)       + (std::stoi(b_h_kerahet.substr(3, 5)))      ;
	int b_h_ogle_td              = (std::stoi(b_h_ogle.substr(0, 2)) * 60)          + (std::stoi(b_h_ogle.substr(3, 5)))         ;
	int b_h_ikindi_td            = (std::stoi(b_h_ikindi.substr(0, 2)) * 60)        + (std::stoi(b_h_ikindi.substr(3, 5)))       ;
	int b_h_asr_sani_td          = (std::stoi(b_h_asr_sani.substr(0, 2)) * 60)      + (std::stoi(b_h_asr_sani.substr(3, 5)))     ;
	int b_h_isfirar_sems_td      = (std::stoi(b_h_isfirar_sems.substr(0, 2)) * 60)  + (std::stoi(b_h_isfirar_sems.substr(3, 5))) ;
	int b_h_kible_saati_td       = (std::stoi(b_h_kible_saati.substr(0, 2)) * 60)   + (std::stoi(b_h_kible_saati.substr(3, 5)))  ;

	int b_h_aksam_td_t         = 0;
	int b_h_istibak_nucum_td_t = b_h_istibak_nucum_td  - b_h_aksam_td        ;
	int b_h_yatsi_td_t         = b_h_yatsi_td          - b_h_aksam_td        ;
	int b_h_isa_sani_td_t      = b_h_isa_sani_td       - b_h_aksam_td        ;
	int b_h_imsak_td_t         = (1440 - b_h_aksam_td) + b_h_imsak_td        ; //1440 bir günün toplam dakikası
	int b_h_sabah_td_t         = (1440 - b_h_aksam_td) + b_h_sabah_td        ;
	int b_h_gunes_td_t         = (1440 - b_h_aksam_td) + b_h_gunes_td        ;
	int b_h_israk_td_t         = (1440 - b_h_aksam_td) + b_h_israk_td        ;
	int b_h_kerahet_td_t       = (1440 - b_h_aksam_td) + b_h_kerahet_td      ;
	int b_h_ogle_td_t          = (1440 - b_h_aksam_td) + b_h_ogle_td         ;
	int b_h_ikindi_td_t        = (1440 - b_h_aksam_td) + b_h_ikindi_td       ;
	int b_h_asr_sani_td_t      = (1440 - b_h_aksam_td) + b_h_asr_sani_td     ;
	int b_h_isfirar_sems_td_t  = (1440 - b_h_aksam_td) + b_h_isfirar_sems_td ;
	int b_h_kible_saati_td_t   = (1440 - b_h_aksam_td) + b_h_kible_saati_td  ;

	zaman::aksam = "00:00";
	zaman::istibak_nucum.append( std::to_string(int(b_h_istibak_nucum_td_t / 60))  + ":" + std::to_string(int(b_h_istibak_nucum_td_t % 60)));
	zaman::yatsi.append(         std::to_string(int(b_h_yatsi_td_t / 60))          + ":" + std::to_string(int(b_h_yatsi_td_t % 60)))        ;
	zaman::isa_sani.append(      std::to_string(int(b_h_isa_sani_td_t / 60))       + ":" + std::to_string(int(b_h_isa_sani_td_t % 60)))     ;
	zaman::imsak.append(         std::to_string(int(b_h_imsak_td_t / 60))          + ":" + std::to_string(int(b_h_imsak_td_t % 60)))        ;
	zaman::sabah.append(         std::to_string(int(b_h_sabah_td_t / 60))          + ":" + std::to_string(int(b_h_sabah_td_t % 60)))        ;
	zaman::gunes.append(         std::to_string(int(b_h_gunes_td_t / 60))          + ":" + std::to_string(int(b_h_gunes_td_t % 60)))        ;
	zaman::israk.append(         std::to_string(int(b_h_israk_td_t / 60))          + ":" + std::to_string(int(b_h_israk_td_t % 60)))        ;
	zaman::kerahet.append(       std::to_string(int(b_h_kerahet_td_t / 60))        + ":" + std::to_string(int(b_h_kerahet_td_t % 60)))      ;
	zaman::ogle.append(          std::to_string(int(b_h_ogle_td_t / 60))           + ":" + std::to_string(int(b_h_ogle_td_t % 60)))         ;
	zaman::ikindi.append(        std::to_string(int(b_h_ikindi_td_t / 60))         + ":" + std::to_string(int(b_h_ikindi_td_t % 60)))       ;
	zaman::asr_sani.append(      std::to_string(int(b_h_asr_sani_td_t / 60))       + ":" + std::to_string(int(b_h_asr_sani_td_t % 60)))     ;
	zaman::isfirar_sems.append(  std::to_string(int(b_h_isfirar_sems_td_t / 60))   + ":" + std::to_string(int(b_h_isfirar_sems_td_t % 60))) ;
	zaman::kible_saati.append(   std::to_string(int(b_h_kible_saati_td_t / 60))    + ":" + std::to_string(int(b_h_kible_saati_td_t % 60)))  ;

	int hrist_zaman_td      = ((hrist_saat * 60) * 60) + (hrist_dakika * 60) + hrist_saniye;
	int hrist_zaman_td_t    = ((1440 - b_h_aksam_td)*60) + hrist_zaman_td                  ;

	zaman::saat      =  int(((hrist_zaman_td_t / 60)/60 )%12);
	zaman::dakika    =  int((hrist_zaman_td_t/ 60) % 60)     ;
	zaman::saniye    =  int((hrist_zaman_td_t) % 60)         ;

	zaman::simdiki_zaman_turk.append(std::to_string(zaman::saat)    + ":" +   std::to_string(zaman::dakika)   + ":" +   std::to_string(zaman::saniye));
};
void zaman::vkt_hrist_v_d()
{
};
void zaman::vkt_turk_v_d()
{
};

void zaman::sat_hrist_v_d()
{
	zaman::hrist_saat   = zaman::ltm->tm_hour;
	zaman::hrist_dakika = zaman::ltm->tm_min ;
	zaman::hrist_saniye = zaman::ltm->tm_sec ;
};
void zaman::sat_turk_v_d()
{
};




void zaman::takvim_v_d()
{
	tkvm_hrist_v_d();
	tkvm_turk_v_d() ;
};
void zaman::vakit_v_d()
{
	vkt_karisik_gecici();
	vkt_hrist_v_d();
	vkt_turk_v_d() ;
};
void zaman::saat_v_d()
{
	sat_hrist_v_d();
	sat_turk_v_d() ;
};



void zaman::gos_turk_v()
{
	std::cout << "__TURK__            Topluca   : " << "" << std::endl << std::endl;

	std::cout << "__TURK__            Sene      : " << zaman::rakam_sene << std::endl;
	std::cout << "__TURK__            Ay        : " << zaman::rakam_ay << ". ay" << std::endl;
	std::cout << "__TURK__ (Yilin)    Gun       : " << zaman::rakam_gun_senenin << ". gunu" << std::endl;
	std::cout << "__TURK__ (Ayin)     Gun       : " << zaman::rakam_gun_ayin << ". gunu" << std::endl;
	std::cout << "__TURK__ (Haftanin) Gun       : " << zaman::rakam_gun_haftanin << ". gunu" << std::endl << std::endl;

	std::cout << "__TURK__ saat ve dakika       : " << simdiki_zaman_turk << std::endl;
	std::cout << "__TURK__ Saat                 : " << zaman::saat << std::endl;
	std::cout << "__TURK__ Dakika               : " << zaman::dakika << std::endl;
	std::cout << "__TURK__ Saniye               : " << zaman::saniye << std::endl << std::endl;

	std::cout << "__TURK__ aksam                : " << zaman::aksam << std::endl;
	std::cout << "__TURK__ istibak-i nucum      : " << zaman::istibak_nucum << std::endl;
	std::cout << "__TURK__ yatsi (isa-i evvel)  : " << zaman::yatsi << std::endl;
	std::cout << "__TURK__ isa-i sani           : " << zaman::isa_sani << std::endl;
	std::cout << "__TURK__ imsak                : " << zaman::imsak << std::endl;
	std::cout << "__TURK__ sabah                : " << zaman::sabah << std::endl;
	std::cout << "__TURK__ gunes                : " << zaman::gunes << std::endl;
	std::cout << "__TURK__ israk                : " << zaman::israk << std::endl;
	std::cout << "__TURK__ kerahet              : " << zaman::kerahet << std::endl;
	std::cout << "__TURK__ ogle                 : " << zaman::ogle << std::endl;
	std::cout << "__TURK__ ikindi               : " << zaman::ikindi << std::endl;
	std::cout << "__TURK__ asr-i sani           : " << zaman::asr_sani << std::endl;
	std::cout << "__TURK__ isfirar-i sems       : " << zaman::isfirar_sems << std::endl;
	std::cout << "__TURK__ kible saati          : " << zaman::kible_saati << std::endl;

	std::cout << std::endl;
};
void zaman::gos_hrist_v()
{
	std::cout << std::endl << std::endl << std::endl << std::endl;

	std::cout << "(hrist) (ing)      Topluca    : " << zaman::dt << std::endl ;

	std::cout << "(hrist)            Sene       : " << zaman::hrist_rakam_sene << std::endl ;
	std::cout << "(hrist)            Ay         : " << zaman::hrist_rakam_ay << ". ay" << std::endl;
	std::cout << "(hrist) (Yilin)    Gun        : " << zaman::hrist_rakam_gun_senenin << ". gunu" << std::endl;
	std::cout << "(hrist) (Ayin)     Gun        : " << zaman::hrist_rakam_gun_ayin << ". gunu" << std::endl;
	std::cout << "(hrist) (Haftanin) Gun        : " << zaman::hrist_rakam_gun_haftanin << ". gunu" << std::endl << std::endl;

	std::cout << "(hrist) Saat                  : " << zaman::hrist_saat << std::endl;
	std::cout << "(hrist) Dakika                : " << zaman::hrist_dakika << std::endl;
	std::cout << "(hrist) Saniye                : " << zaman::hrist_saniye << std::endl << std::endl;

	std::cout << "(hrist) aksam                 : " << zaman::b_h_aksam << std::endl;
	std::cout << "(hrist) istibak-i nucum       : " << zaman::b_h_istibak_nucum << std::endl;
	std::cout << "(hrist) yatsi (isa-i evvel)   : " << zaman::b_h_yatsi << std::endl;
	std::cout << "(hrist) isa-i sani            : " << zaman::b_h_isa_sani << std::endl;
	std::cout << "(hrist) imsak                 : " << zaman::b_h_imsak << std::endl;
	std::cout << "(hrist) sabah                 : " << zaman::b_h_sabah << std::endl;
	std::cout << "(hrist) gunes                 : " << zaman::b_h_gunes << std::endl;
	std::cout << "(hrist) israk                 : " << zaman::b_h_israk << std::endl;
	std::cout << "(hrist) kerahet               : " << zaman::b_h_kerahet << std::endl;
	std::cout << "(hrist) ogle                  : " << zaman::b_h_ogle << std::endl;
	std::cout << "(hrist) ikindi                : " << zaman::b_h_ikindi << std::endl;
	std::cout << "(hrist) asr-i sani            : " << zaman::b_h_asr_sani << std::endl;
	std::cout << "(hrist) isfirar-i sems        : " << zaman::b_h_isfirar_sems << std::endl;
	std::cout << "(hrist) kible saati           : " << zaman::b_h_kible_saati << std::endl;
};

zaman::zaman()
{
	takvim_v_d();
	saat_v_d();
	vakit_v_d();

	gos_turk_v();
	gos_hrist_v();
}
zaman::~zaman()
{
}
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
