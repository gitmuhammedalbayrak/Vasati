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

void Zaman::tkvm_hrist_v_d()
{
	//zaman paketinin temel verileri;
	Zaman::now = time(0);
	Zaman::ltm = localtime(&now);
	Zaman::dt = ctime(&now);

	Zaman::hrist_rakam_gun_senenin = (1 + Zaman::ltm->tm_yday);
	Zaman::hrist_rakam_gun_ayin = Zaman::ltm->tm_mday;
	Zaman::hrist_rakam_gun_haftanin = Zaman::ltm->tm_wday;
	Zaman::hrist_rakam_sene = (1900 + Zaman::ltm->tm_year);
	Zaman::hrist_rakam_ay = (1 + Zaman::ltm->tm_mon);
};
void Zaman::tkvm_turk_v_d()
{
	Zaman::rakam_gun_haftanin = Zaman::hrist_rakam_gun_haftanin;

	int a_rakami = Zaman::hrist_rakam_sene - 621;
	int b_rakami = a_rakami / 33;
	int c_rakami = a_rakami + b_rakami;

	Zaman::rakam_sene = c_rakami;
};

void Zaman::vkt_karisik_gecici()
{

	Zaman::dosya_adresi = "include/XML/Vakitler.xml";
	Zaman::dosya.load_file(Zaman::dosya_adresi);
	Zaman::sehir = dosya.child("cityinfo");

	char buffer[5];
	std::sprintf(buffer, "%d", Zaman::hrist_rakam_gun_senenin);
	const char *h_r_g_s_c_c = buffer; //şu kısaltmaların açıklamasına dikkat etmeliyim: mesela buradaki sın iki c harfinin anlamını unutmuşum ne köt.

	Zaman::xml_bu_gun = Zaman::sehir.find_child_by_attribute("prayertimes", "dayofyear", h_r_g_s_c_c).text().get();

	Zaman::b_h_aksam = Zaman::xml_bu_gun.substr(50, 6);
	Zaman::b_h_istibak_nucum = Zaman::xml_bu_gun.substr(56, 6);
	Zaman::b_h_yatsi = Zaman::xml_bu_gun.substr(62, 6);
	Zaman::b_h_isa_sani = Zaman::xml_bu_gun.substr(68, 6);

	//buradaka kodları yeniliyoruz çünkü bir sonraki gün kılacağız verileri:

	std::sprintf(buffer, "%d", (Zaman::hrist_rakam_gun_senenin + 1));

	Zaman::xml_bu_gun = Zaman::sehir.find_child_by_attribute("prayertimes", "dayofyear", h_r_g_s_c_c).text().get();

	Zaman::b_h_imsak = Zaman::xml_bu_gun.substr(0, 4);
	Zaman::b_h_sabah = Zaman::xml_bu_gun.substr(5, 5);
	Zaman::b_h_gunes = Zaman::xml_bu_gun.substr(10, 5);
	Zaman::b_h_israk = Zaman::xml_bu_gun.substr(15, 5);
	Zaman::b_h_kerahet = Zaman::xml_bu_gun.substr(20, 6);
	Zaman::b_h_ogle = Zaman::xml_bu_gun.substr(26, 6);
	Zaman::b_h_ikindi = Zaman::xml_bu_gun.substr(32, 6);
	Zaman::b_h_asr_sani = Zaman::xml_bu_gun.substr(38, 6);
	Zaman::b_h_isfirar_sems = Zaman::xml_bu_gun.substr(44, 6);
	Zaman::b_h_kible_saati = Zaman::xml_bu_gun.substr(74, 6);

	// şimdi vakitlerin dakika hesabı yapılacak yekunü alınacak ve üzerinden işlem yapılacak.

	//td : toplam dakika (aşağıdaki kısaltmalar)

	int b_h_aksam_td = (std::stoi(b_h_aksam.substr(0, 2)) * 60) + (std::stoi(b_h_aksam.substr(3, 5)));
	int b_h_istibak_nucum_td = (std::stoi(b_h_istibak_nucum.substr(0, 2)) * 60) + (std::stoi(b_h_istibak_nucum.substr(3, 5)));
	int b_h_yatsi_td = (std::stoi(b_h_yatsi.substr(0, 2)) * 60) + (std::stoi(b_h_yatsi.substr(3, 5)));
	int b_h_isa_sani_td = (std::stoi(b_h_isa_sani.substr(0, 2)) * 60) + (std::stoi(b_h_isa_sani.substr(3, 5)));
	int b_h_imsak_td = (std::stoi(b_h_imsak.substr(0, 2)) * 60) + (std::stoi(b_h_imsak.substr(2, 5)));
	int b_h_sabah_td = (std::stoi(b_h_sabah.substr(0, 2)) * 60) + (std::stoi(b_h_sabah.substr(2, 5)));
	int b_h_gunes_td = (std::stoi(b_h_gunes.substr(0, 2)) * 60) + (std::stoi(b_h_gunes.substr(2, 5)));
	int b_h_israk_td = (std::stoi(b_h_israk.substr(0, 2)) * 60) + (std::stoi(b_h_israk.substr(2, 5)));
	int b_h_kerahet_td = (std::stoi(b_h_kerahet.substr(0, 2)) * 60) + (std::stoi(b_h_kerahet.substr(3, 5)));
	int b_h_ogle_td = (std::stoi(b_h_ogle.substr(0, 2)) * 60) + (std::stoi(b_h_ogle.substr(3, 5)));
	int b_h_ikindi_td = (std::stoi(b_h_ikindi.substr(0, 2)) * 60) + (std::stoi(b_h_ikindi.substr(3, 5)));
	int b_h_asr_sani_td = (std::stoi(b_h_asr_sani.substr(0, 2)) * 60) + (std::stoi(b_h_asr_sani.substr(3, 5)));
	int b_h_isfirar_sems_td = (std::stoi(b_h_isfirar_sems.substr(0, 2)) * 60) + (std::stoi(b_h_isfirar_sems.substr(3, 5)));
	int b_h_kible_saati_td = (std::stoi(b_h_kible_saati.substr(0, 2)) * 60) + (std::stoi(b_h_kible_saati.substr(3, 5)));

	int turk_saati_baslangic_dakikasi_moderne_gore = b_h_aksam_td;

	int b_h_aksam_td_t = 0;
	int b_h_istibak_nucum_td_t = b_h_istibak_nucum_td - b_h_aksam_td;
	int b_h_yatsi_td_t = b_h_yatsi_td - b_h_aksam_td;
	int b_h_isa_sani_td_t = b_h_isa_sani_td - b_h_aksam_td;
	int b_h_imsak_td_t = (1440 - b_h_aksam_td) + b_h_imsak_td; //1440 bir günün toplam dakikası
	int b_h_sabah_td_t = (1440 - b_h_aksam_td) + b_h_sabah_td;
	int b_h_gunes_td_t = (1440 - b_h_aksam_td) + b_h_gunes_td;
	int b_h_israk_td_t = (1440 - b_h_aksam_td) + b_h_israk_td;
	int b_h_kerahet_td_t = (1440 - b_h_aksam_td) + b_h_kerahet_td;
	int b_h_ogle_td_t = (1440 - b_h_aksam_td) + b_h_ogle_td;
	int b_h_ikindi_td_t = (1440 - b_h_aksam_td) + b_h_ikindi_td;
	int b_h_asr_sani_td_t = (1440 - b_h_aksam_td) + b_h_asr_sani_td;
	int b_h_isfirar_sems_td_t = (1440 - b_h_aksam_td) + b_h_isfirar_sems_td;
	int b_h_kible_saati_td_t = (1440 - b_h_aksam_td) + b_h_kible_saati_td;

	Zaman::aksam = "00:00";
	Zaman::istibak_nucum.append(std::to_string(int(b_h_istibak_nucum_td_t / 60)) + ":" + std::to_string(int(b_h_istibak_nucum_td_t % 60)));
	Zaman::yatsi.append(std::to_string(int(b_h_yatsi_td_t / 60)) + ":" + std::to_string(int(b_h_yatsi_td_t % 60)));
	Zaman::isa_sani.append(std::to_string(int(b_h_isa_sani_td_t / 60)) + ":" + std::to_string(int(b_h_isa_sani_td_t % 60)));
	Zaman::imsak.append(std::to_string(int(b_h_imsak_td_t / 60)) + ":" + std::to_string(int(b_h_imsak_td_t % 60)));
	Zaman::sabah.append(std::to_string(int(b_h_sabah_td_t / 60)) + ":" + std::to_string(int(b_h_sabah_td_t % 60)));
	Zaman::gunes.append(std::to_string(int(b_h_gunes_td_t / 60)) + ":" + std::to_string(int(b_h_gunes_td_t % 60)));
	Zaman::israk.append(std::to_string(int(b_h_israk_td_t / 60)) + ":" + std::to_string(int(b_h_israk_td_t % 60)));
	Zaman::kerahet.append(std::to_string(int(b_h_kerahet_td_t / 60)) + ":" + std::to_string(int(b_h_kerahet_td_t % 60)));
	Zaman::ogle.append(std::to_string(int(b_h_ogle_td_t / 60)) + ":" + std::to_string(int(b_h_ogle_td_t % 60)));
	Zaman::ikindi.append(std::to_string(int(b_h_ikindi_td_t / 60)) + ":" + std::to_string(int(b_h_ikindi_td_t % 60)));
	Zaman::asr_sani.append(std::to_string(int(b_h_asr_sani_td_t / 60)) + ":" + std::to_string(int(b_h_asr_sani_td_t % 60)));
	Zaman::isfirar_sems.append(std::to_string(int(b_h_isfirar_sems_td_t / 60)) + ":" + std::to_string(int(b_h_isfirar_sems_td_t % 60)));
	Zaman::kible_saati.append(std::to_string(int(b_h_kible_saati_td_t / 60)) + ":" + std::to_string(int(b_h_kible_saati_td_t % 60)));

	int hrist_zaman_td      = ((hrist_saat * 60) * 60) + (hrist_dakika * 60) + hrist_saniye;
	int hrist_zaman_td_t    = ((1440 - b_h_aksam_td)*60) + hrist_zaman_td;

	Zaman::saat      =  int(((hrist_zaman_td_t / 60)/60 )%12);
	Zaman::dakika    =  int((hrist_zaman_td_t/ 60) % 60);
	Zaman::saniye    =  int((hrist_zaman_td_t) % 60);

	Zaman::simdiki_zaman_turk.append(std::to_string(Zaman::saat) + ":" + std::to_string(Zaman::dakika) + ":" + std::to_string(Zaman::saniye));
};
void Zaman::vkt_hrist_v_d()
{
};
void Zaman::vkt_turk_v_d()
{
};

void Zaman::sat_hrist_v_d()
{
	Zaman::hrist_saat = (Zaman::ltm->tm_hour);
	Zaman::hrist_dakika = Zaman::ltm->tm_min;
	Zaman::hrist_saniye = Zaman::ltm->tm_sec;
};
void Zaman::sat_turk_v_d()
{
};

void Zaman::takvim_v_d()
{
	tkvm_hrist_v_d();
	tkvm_turk_v_d();
};
void Zaman::vakit_v_d()
{
	vkt_karisik_gecici();
	vkt_hrist_v_d();
	vkt_turk_v_d();
};
void Zaman::saat_v_d()
{
	sat_hrist_v_d();
	sat_turk_v_d();
};

void Zaman::gos_turk_v()
{
	std::cout << "__TURK__            Topluca   : " << "" << std::endl << std::endl;

	std::cout << "__TURK__            Sene      : " << Zaman::rakam_sene << std::endl;
	std::cout << "__TURK__            Ay        : " << Zaman::rakam_ay << ". ay" << std::endl;
	std::cout << "__TURK__ (Yilin)    Gun       : " << Zaman::rakam_gun_senenin << ". gunu" << std::endl;
	std::cout << "__TURK__ (Ayin)     Gun       : " << Zaman::rakam_gun_ayin << ". gunu" << std::endl;
	std::cout << "__TURK__ (Haftanin) Gun       : " << Zaman::rakam_gun_haftanin << ". gunu" << std::endl << std::endl;

	std::cout << "__TURK__ saat ve dakika       : " << simdiki_zaman_turk << std::endl;
	std::cout << "__TURK__ Saat                 : " << Zaman::saat << std::endl;
	std::cout << "__TURK__ Dakika               : " << Zaman::dakika << std::endl;
	std::cout << "__TURK__ Saniye               : " << Zaman::saniye << std::endl << std::endl;

	std::cout << "__TURK__ aksam                : " << Zaman::aksam << std::endl;
	std::cout << "__TURK__ istibak-i nucum      : " << Zaman::istibak_nucum << std::endl;
	std::cout << "__TURK__ yatsi (isa-i evvel)  : " << Zaman::yatsi << std::endl;
	std::cout << "__TURK__ isa-i sani           : " << Zaman::isa_sani << std::endl;
	std::cout << "__TURK__ imsak                : " << Zaman::imsak << std::endl;
	std::cout << "__TURK__ sabah                : " << Zaman::sabah << std::endl;
	std::cout << "__TURK__ gunes                : " << Zaman::gunes << std::endl;
	std::cout << "__TURK__ israk                : " << Zaman::israk << std::endl;
	std::cout << "__TURK__ kerahet              : " << Zaman::kerahet << std::endl;
	std::cout << "__TURK__ ogle                 : " << Zaman::ogle << std::endl;
	std::cout << "__TURK__ ikindi               : " << Zaman::ikindi << std::endl;
	std::cout << "__TURK__ asr-i sani           : " << Zaman::asr_sani << std::endl;
	std::cout << "__TURK__ isfirar-i sems       : " << Zaman::isfirar_sems << std::endl;
	std::cout << "__TURK__ kible saati          : " << Zaman::kible_saati << std::endl;

	std::cout << std::endl;
};
void Zaman::gos_hrist_v()
{
	std::cout << std::endl << std::endl << std::endl << std::endl;

	std::cout << "(hrist) (ing)      Topluca    : " << Zaman::dt << std::endl ;

	std::cout << "(hrist)            Sene       : " << Zaman::hrist_rakam_sene << std::endl ;
	std::cout << "(hrist)            Ay         : " << Zaman::hrist_rakam_ay << ". ay" << std::endl;
	std::cout << "(hrist) (Yilin)    Gun        : " << Zaman::hrist_rakam_gun_senenin << ". gunu" << std::endl;
	std::cout << "(hrist) (Ayin)     Gun        : " << Zaman::hrist_rakam_gun_ayin << ". gunu" << std::endl;
	std::cout << "(hrist) (Haftanin) Gun        : " << Zaman::hrist_rakam_gun_haftanin << ". gunu" << std::endl << std::endl;

	std::cout << "(hrist) Saat                  : " << Zaman::hrist_saat << std::endl;
	std::cout << "(hrist) Dakika                : " << Zaman::hrist_dakika << std::endl;
	std::cout << "(hrist) Saniye                : " << Zaman::hrist_saniye << std::endl << std::endl;

	std::cout << "(hrist) aksam                 : " << Zaman::b_h_aksam << std::endl;
	std::cout << "(hrist) istibak-i nucum       : " << Zaman::b_h_istibak_nucum << std::endl;
	std::cout << "(hrist) yatsi (isa-i evvel)   : " << Zaman::b_h_yatsi << std::endl;
	std::cout << "(hrist) isa-i sani            : " << Zaman::b_h_isa_sani << std::endl;
	std::cout << "(hrist) imsak                 : " << Zaman::b_h_imsak << std::endl;
	std::cout << "(hrist) sabah                 : " << Zaman::b_h_sabah << std::endl;
	std::cout << "(hrist) gunes                 : " << Zaman::b_h_gunes << std::endl;
	std::cout << "(hrist) israk                 : " << Zaman::b_h_israk << std::endl;
	std::cout << "(hrist) kerahet               : " << Zaman::b_h_kerahet << std::endl;
	std::cout << "(hrist) ogle                  : " << Zaman::b_h_ogle << std::endl;
	std::cout << "(hrist) ikindi                : " << Zaman::b_h_ikindi << std::endl;
	std::cout << "(hrist) asr-i sani            : " << Zaman::b_h_asr_sani << std::endl;
	std::cout << "(hrist) isfirar-i sems        : " << Zaman::b_h_isfirar_sems << std::endl;
	std::cout << "(hrist) kible saati           : " << Zaman::b_h_kible_saati << std::endl;
};

Zaman::Zaman()
{
	takvim_v_d();
	saat_v_d();
	vakit_v_d();

	gos_turk_v();
	gos_hrist_v();
}
Zaman::~Zaman()
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
