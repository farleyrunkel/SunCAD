#include <wx/wx.h>

// 主应用类，继承自 wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// 主窗口类，继承自 wxFrame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

// 为主应用类实现 `wxIMPLEMENT_APP`
wxIMPLEMENT_APP(MyApp);

// 初始化应用
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Hello wxWidgets");  // 创建主窗口
    frame->Show(true);  // 显示主窗口
    return true;
}

// 主窗口的构造函数
MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title) {
    // 创建菜单栏
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(1, "&Hello...\tCtrl-H", "Show Hello message");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);

    // 绑定事件
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, 1);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}

// "Hello" 菜单项事件处理
void MyFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello, wxWidgets!");
}

// "Exit" 菜单项事件处理
void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);  // 关闭窗口
}
