<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>GameBase::IMainWindow</name>
    <filename>class_game_base_1_1_i_main_window.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual HWND</type>
      <name>VOnInitialization</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>a3bff4313b310197d86a1f656e7b7a45b</anchor>
      <arglist>(const HINSTANCE &amp;hInstance, const int &amp;nCmdShow, IBaseApp *const pGame)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VToggleFullScreen</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>a38c000af29a29328c6e27229999ef969</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VCleanup</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>af3d6381dd99edc73fcfe42664f963d64</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GAMEBASE_API IMainWindow *const</type>
      <name>GetInstance</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>ab179d6612855e82e6c11a70356e4e938</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GAMEBASE_API void</type>
      <name>Destroy</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>a4acfddfd9e75e82f461d28b50c5be201</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GameBase::cMainWindow</name>
    <filename>class_game_base_1_1c_main_window.html</filename>
    <base>GameBase::IMainWindow</base>
    <base>Base::cNonCopyable</base>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Create</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a846b01159cf52e8bc090d7d6680276ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>HWND</type>
      <name>VOnInitialization</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a55bc204edefba391591eb99687a7a83e</anchor>
      <arglist>(const HINSTANCE &amp;hInstance, const int &amp;nCmdShow, IBaseApp *const pGame)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VToggleFullScreen</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a332eb3c53a163519c8063d8ed920d0cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VCleanup</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a163a373aff3de5e3365492add6ffcada</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RegisterWin</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>af22ea267f5a12c3f297a1d0af300b4bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CreateMyWindow</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a0957f015bad2322bb518c96bfb4968da</anchor>
      <arglist>(const int &amp;nCmdShow, const Base::cString &amp;lpWindowTitle)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>LRESULT CALLBACK</type>
      <name>WndProc</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a34c0302fa66b64a61aaf2830ad28b134</anchor>
      <arglist>(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnWindowDestroyed</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a706622ac9bba08ed54be1c8afb0eac75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetDisplayResolution</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>ac7c58c9c7715cfee9477b378e4cf21dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CalculateWindowRect</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>af52731cc6c5cd63df04d76e89e30c2fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static LRESULT CALLBACK</type>
      <name>StaticWndProc</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>ae300f890e0792e50e0311d7f3b8e8614</anchor>
      <arglist>(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const DWORD</type>
      <name>m_kdwFullScreenStyle</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a49288199090e86f10f71a9ffcac9543a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const DWORD</type>
      <name>m_kdwWindowedStyle</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a6fd476492260b48c4e6f105e817b5325</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>HWND</type>
      <name>m_Hwnd</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a904ace28c221002cdcb529a31731601f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>HINSTANCE</type>
      <name>m_hInstance</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a5f75deceeb79ada4746379fa9d092aeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>IBaseApp *</type>
      <name>m_pGame</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>aa599ab9886823365c4ce532a58c5150c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>RECT</type>
      <name>m_windowRect</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>ae9488a5cb404a914050ca42ceb185105</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
