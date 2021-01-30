/////////////////////////////////////////////////////////////////////
//                                                                 //
//   ����d�q��H Library                                          //
//                                                                 //
//             USB FX2 Interface                                   //
//                                                                 //
//   (C)Copyright 2005-2006 ���d,Nahitech Inc. All rights reserved.//
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

// �X��USB�{�[�h�̎��ʏ��
typedef struct USBBoardInfo {
	int           id;              // USBOpenById()�֐��Ŏw�肷��ׂ�ID���Z�b�g����Ė߂�
	WCHAR         descriptor[32];  // USB��String Descriptor(31�����܂�)���Z�b�g����Ė߂�
	unsigned char option[32];      // �e�{�[�h�ɏ������܂ꂽ���ʏ�񂪃Z�b�g����Ė߂�
} USBBoardInfo;

// �{�[�h��ID���������܂�Ă���EEPROM�̃A�h���X
#define BOARD_ID_ADDR   0x1fe0

////////////////////////////////////////////////////////////////////////////////////////
//
//          �{�[�h���擾�E����֐�
//
////////////////////////////////////////////////////////////////////////////////////////

// �����USB-FPGA�{�[�h���ڑ�����Ă��邩�𐔂���֐�
// -1��Ԃ����牽�炩�̃G���[
// 0��Ԃ�����A�{�[�h�͐ڑ�����Ă��Ȃ�(�G���[�ł͂Ȃ�)
// ���̐���Ԃ�����A�{�[�h�̍ő�C���X�^���X��
// �y�܂���������Ă��Ȃ��z
TKUSB_API
DWORD WINAPI USBGetMaxInstance();

// �I�[�v�����Ă���{�[�h�̏��𓾂�
// USBBoardInfo�^�\���̗̂̈���m�ۂ��āA������result�Ɏw�肵�ČĂяo����
// �e�t�B�[���h���Z�b�g����Ė߂�
TKUSB_API
BOOL WINAPI USBGetBoardInfo(USBBoardInfo *result);

// 32�o�C�g�̌ŗL���ʏ�����������
TKUSB_API
BOOL WINAPI USBSetBoardUserId(unsigned char id[32]);

// �f�o�C�X�h���C�o�̃o�[�W�����𒲂ׂ�
// �y�܂���������Ă��Ȃ��z
TKUSB_API
unsigned long WINAPI USBGetDriverVersion(void);

// �t�@�[���E�F�A(EZ-USB FX2��̃v���O�����̂���)�̃o�[�W�����𒲂ׂ�
// �y�܂���������Ă��Ȃ��z
TKUSB_API
unsigned long WINAPI USBGetFirmwareVersion(void);

// EZ-USB FX2�ɐڑ����ꂽEEPROM��ǂݏo���֐� 
// EEPROM��8k�o�C�g�Baddr��len��32�o�C�g�P�ʂŎw�肷�邱��
// �O��4k�o�C�g�̓t�@�[���E�F�A���i�[����Ă���
// �㔼4k�o�C�g�̓��[�U�����R�Ɏg���Ă悢
TKUSB_API
BOOL WINAPI USBReadEEPROM(unsigned short addr,unsigned char *data,int len);

// EZ-USB FX2�ɐڑ����ꂽEEPROM������������֐�
// addr,len��32�o�C�g�P��
// �t�@�[���E�F�A�̈�͏����������Ȃ�
TKUSB_API
BOOL WINAPI USBWriteEEPROM(unsigned short addr,unsigned char *data,int len);

// WriteEEPROM�Ńt�@�[���E�F�A�̈�(0x0000�`0x3FFF)�̏���������������֐�
// ���̊֐������s����ƁAWriteEEPROM�Ńt�@�[���E�F�A��������������悤�ɂȂ�
// keyword�ɂ́A"REWRITE"�Ǝw�肷��
TKUSB_API
BOOL WINAPI USBUnlockEEPROMFirmArea(const char *keyword);

////////////////////////////////////////////////////////////////////////////////////////
//
//          USB��{����
//
////////////////////////////////////////////////////////////////////////////////////////

// �ŏ��Ɍ�������SP6�{�[�h���I�[�v������
TKUSB_API
BOOL WINAPI USBOpen(void);

// ID���w�肵��SP6�{�[�h���I�[�v������
TKUSB_API
BOOL WINAPI USBOpenByID(int id);

// USB�̃N���[�Y
TKUSB_API
void WINAPI USBClose(void);

// �f�[�^��������(OUT�]��)
TKUSB_API
BOOL WINAPI USBWriteData(unsigned char *buffer,int len,unsigned short flag);

// �f�[�^�ǂݏo��(IN�]��)
TKUSB_API
BOOL WINAPI USBReadData(unsigned char *buffer,int len,unsigned short flag);

// �A�h���X�w��t���f�[�^��������(OUT�]��)(�^�C���A�E�g����)
TKUSB_API
BOOL WINAPI USBWriteSDRAM(unsigned long addr,unsigned char *buffer,int len,unsigned short flag);

// �A�h���X�w��t���f�[�^�̓ǂݏo��(IN�]��)(�^�C���A�E�g����)
TKUSB_API
BOOL WINAPI USBReadSDRAM(unsigned long addr,unsigned char *buffer,int len,unsigned short flag);

// �^�C���A�E�g���Ԃ̐ݒ�(ms�P��)
TKUSB_API
BOOL WINAPI USBSetTimeout(unsigned long millisecond);

// ���݂̓]���̃L�����Z���ƃ��Z�b�g
TKUSB_API
BOOL WINAPI USBReset(void);

////////////////////////////////////////////////////////////////////////////////////////
//
//          USB-JTAG����
//
////////////////////////////////////////////////////////////////////////////////////////

// USB-JTAG���[�h��L���ɂ��邩�ǂ�����ݒ肷��
// USB-JTAG���[�h�ł̓A�v���P�[�V�����̒ʐM�͂ł��Ȃ�
// Enable��1�ɂ���ƁAUSB-JTAG���[�h�B
// Enable��0�ɂ���ƁA�ʏ퓮�샂�[�h�B
TKUSB_API
BOOL WINAPI USBSetSmajMode(BOOL enable);

// USB-JTAG���[�h���ʏ퓮�샂�[�h���𒲂ׂ�
TKUSB_API
BOOL WINAPI USBGetSmajMode(BOOL *result);

// BitStream�f�[�^���w�肵�āAFPGA��JTAG�R���t�B�M�����[�V��������
TKUSB_API
BOOL WINAPI USBConfigFPGA(unsigned char *bitStream);


////////////////////////////////////////////////////////////////////////////////////////
//
//          �f�o�b�O�p�֐�
//
////////////////////////////////////////////////////////////////////////////////////////

TKUSB_API
void WINAPI USBEnableDebug(void);

TKUSB_API
void WINAPI USBShowStatus(void);

#endif

