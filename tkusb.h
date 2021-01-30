/////////////////////////////////////////////////////////////////////
//                                                                 //
//   特殊電子回路 Library                                          //
//                                                                 //
//             USB FX2 Interface                                   //
//                                                                 //
//   (C)Copyright 2005-2006 特電,Nahitech Inc. All rights reserved.//
//                                                                 //
/////////////////////////////////////////////////////////////////////

#ifndef TKUSB_H
#define TKUSB_H

#ifndef TKUSB_API
  #ifdef __cplusplus
   #define TKUSB_API extern "C" __declspec(dllimport)
  #else
   #define TKUSB_API __declspec(dllimport)
  #endif
#endif

#ifdef __WIN32__
  #include <windows.h>
#endif

// 個々のUSBボードの識別情報
typedef struct USBBoardInfo {
	int           id;              // USBOpenById()関数で指定するべきIDがセットされて戻る
	WCHAR         descriptor[32];  // USBのString Descriptor(31文字まで)がセットされて戻る
	unsigned char option[32];      // 各ボードに書き込まれた識別情報がセットされて戻る
} USBBoardInfo;

// ボードのIDが書き込まれているEEPROMのアドレス
#define BOARD_ID_ADDR   0x1fe0

////////////////////////////////////////////////////////////////////////////////////////
//
//          ボード情報取得・操作関数
//
////////////////////////////////////////////////////////////////////////////////////////

// 何台のUSB-FPGAボードが接続されているかを数える関数
// -1を返したら何らかのエラー
// 0を返したら、ボードは接続されていない(エラーではない)
// 正の数を返したら、ボードの最大インスタンス数
// 【まだ実装されていない】
TKUSB_API
DWORD WINAPI USBGetMaxInstance();

// オープンしているボードの情報を得る
// USBBoardInfo型構造体の領域を確保して、引数のresultに指定して呼び出すと
// 各フィールドがセットされて戻る
TKUSB_API
BOOL WINAPI USBGetBoardInfo(USBBoardInfo *result);

// 32バイトの固有識別情報を書き込む
TKUSB_API
BOOL WINAPI USBSetBoardUserId(unsigned char id[32]);

// デバイスドライバのバージョンを調べる
// 【まだ実装されていない】
TKUSB_API
unsigned long WINAPI USBGetDriverVersion(void);

// ファームウェア(EZ-USB FX2上のプログラムのこと)のバージョンを調べる
// 【まだ実装されていない】
TKUSB_API
unsigned long WINAPI USBGetFirmwareVersion(void);

// EZ-USB FX2に接続されたEEPROMを読み出す関数 
// EEPROMは8kバイト。addrとlenは32バイト単位で指定すること
// 前半4kバイトはファームウェアが格納されている
// 後半4kバイトはユーザが自由に使ってよい
TKUSB_API
BOOL WINAPI USBReadEEPROM(unsigned short addr,unsigned char *data,int len);

// EZ-USB FX2に接続されたEEPROMを書き換える関数
// addr,lenは32バイト単位
// ファームウェア領域は書き換えられない
TKUSB_API
BOOL WINAPI USBWriteEEPROM(unsigned short addr,unsigned char *data,int len);

// WriteEEPROMでファームウェア領域(0x0000～0x3FFF)の書き換えを許可する関数
// この関数を実行すると、WriteEEPROMでファームウェアを書き換えられるようになる
// keywordには、"REWRITE"と指定する
TKUSB_API
BOOL WINAPI USBUnlockEEPROMFirmArea(const char *keyword);

////////////////////////////////////////////////////////////////////////////////////////
//
//          USB基本操作
//
////////////////////////////////////////////////////////////////////////////////////////

// 最初に見つかったSP6ボードをオープンする
TKUSB_API
BOOL WINAPI USBOpen(void);

// IDを指定してSP6ボードをオープンする
TKUSB_API
BOOL WINAPI USBOpenByID(int id);

// USBのクローズ
TKUSB_API
void WINAPI USBClose(void);

// データ書き込み(OUT転送)
TKUSB_API
BOOL WINAPI USBWriteData(unsigned char *buffer,int len,unsigned short flag);

// データ読み出し(IN転送)
TKUSB_API
BOOL WINAPI USBReadData(unsigned char *buffer,int len,unsigned short flag);

// アドレス指定付きデータ書き込み(OUT転送)(タイムアウトあり)
TKUSB_API
BOOL WINAPI USBWriteSDRAM(unsigned long addr,unsigned char *buffer,int len,unsigned short flag);

// アドレス指定付きデータの読み出し(IN転送)(タイムアウトあり)
TKUSB_API
BOOL WINAPI USBReadSDRAM(unsigned long addr,unsigned char *buffer,int len,unsigned short flag);

// タイムアウト時間の設定(ms単位)
TKUSB_API
BOOL WINAPI USBSetTimeout(unsigned long millisecond);

// 現在の転送のキャンセルとリセット
TKUSB_API
BOOL WINAPI USBReset(void);

////////////////////////////////////////////////////////////////////////////////////////
//
//          USB-JTAG操作
//
////////////////////////////////////////////////////////////////////////////////////////

// USB-JTAGモードを有効にするかどうかを設定する
// USB-JTAGモードではアプリケーションの通信はできない
// Enableを1にすると、USB-JTAGモード。
// Enableを0にすると、通常動作モード。
TKUSB_API
BOOL WINAPI USBSetSmajMode(BOOL enable);

// USB-JTAGモードか通常動作モードかを調べる
TKUSB_API
BOOL WINAPI USBGetSmajMode(BOOL *result);

// BitStreamデータを指定して、FPGAをJTAGコンフィギュレーションする
TKUSB_API
BOOL WINAPI USBConfigFPGA(unsigned char *bitStream);


////////////////////////////////////////////////////////////////////////////////////////
//
//          デバッグ用関数
//
////////////////////////////////////////////////////////////////////////////////////////

TKUSB_API
void WINAPI USBEnableDebug(void);

TKUSB_API
void WINAPI USBShowStatus(void);

#endif

