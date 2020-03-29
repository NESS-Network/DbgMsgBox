//by neurocod as Konstantine Kozachuk, BSD license, 2020.03.29
//see README.md
#include "pch.h"
#include "DbgMsgBox.h"

int main(int argc, char* argv[]) {
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);
	a.setOrganizationName("neurocod");
	a.setOrganizationDomain("neurocod@");
	{
		QFont font = a.font();
		font.setPointSize(12);
		a.setFont(font);
	}
	QString text;
#ifdef Q_OS_WIN
	QCoreApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
	if (argc > 1) {
		auto strTitle = ::GetCommandLineW();
		text = QString::fromWCharArray(strTitle);
	} else {
		text = "no cmd line";
	}
#else
#error
#endif
	DbgMsgBox w;
	w.setTextFromCommandLine(text);
	return w.exec();
}

#ifdef Q_OS_WIN
//in your Windows app launch with:
void msgBox(const std::string& s) {
	std::vector<CHAR> vec;
	for (auto c : s)
		vec.push_back(c);
	vec.push_back(0);

	STARTUPINFOA info;
	ZeroMemory(&info, sizeof(info));
	info.cb = sizeof(info);

	PROCESS_INFORMATION processInfo = {};
	ZeroMemory(&processInfo, sizeof(processInfo));

	BOOL ok = CreateProcessA(R"(D:\dev\DbgMsgBox\x64\Debug\DbgMsgBox.exe)", vec.data(), 0, 0, 0, 0, 0, 0, &info, &processInfo);
	if (ok) {
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
}
#else
//in linux/macos: TODO
void msgBox(const std::string& s) {
	exec(...);
}
#endif