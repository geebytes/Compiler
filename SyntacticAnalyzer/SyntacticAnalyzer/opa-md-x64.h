// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� OPAMDX64_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// OPAMDX64_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef OPAMDX64_EXPORTS
#define OPAMDX64_API __declspec(dllexport)
#else
#define OPAMDX64_API __declspec(dllimport)
#endif

// �����Ǵ� opa-md-x64.dll ������
class OPAMDX64_API Copamdx64 {
public:
	Copamdx64(void);
	// TODO:  �ڴ�������ķ�����
};

extern OPAMDX64_API int nopamdx64;

OPAMDX64_API int fnopamdx64(void);
