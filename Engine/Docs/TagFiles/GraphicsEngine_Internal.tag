<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>Graphics::IBaseControl</name>
    <filename>class_graphics_1_1_i_base_control.html</filename>
    <base>Graphics::IMouseHandler</base>
    <base>Graphics::IKeyboardHandler</base>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VPostMsg</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a8972600b29236f16d4789b127ef880d6</anchor>
      <arglist>(const Base::AppMsg &amp;msg)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VAddChildControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a07ee4776f46c2bd7e5fb4560451445e3</anchor>
      <arglist>(shared_ptr&lt; IBaseControl &gt; pChildControl)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRemoveAllChildren</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>affadc48ccd7ad5391a2a2b7b6e538490</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRemoveChildControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a12e13731d557f352980980d410d8be31</anchor>
      <arglist>(const Base::cString &amp;strControlName)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Graphics::IBaseControl *const</type>
      <name>VFindChildControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a2d2ac6d51b29a59d40e59e7e7f695a6c</anchor>
      <arglist>(const Base::cString &amp;strControlName)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>af2a2085f2732a8a086e35cadcf6e6e41</anchor>
      <arglist>(const ICamera *const pCamera)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetVisible</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a0065c4088fe588f59691538ac2ba870f</anchor>
      <arglist>(bool bIsVisible)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a4158cf0f9d6f1f474ed3016923a80825</anchor>
      <arglist>(const Base::cVector2 &amp;vPosition)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Base::cVector2</type>
      <name>VGetSize</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a6b2968a8bd8ec854e5013bc5efef29ad</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetSize</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a57d862cda8987b6e8aa0805d5ee21e1a</anchor>
      <arglist>(const Base::cVector2 &amp;vSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRegisterCallBack</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a917dbf83272eaa12cb4654edda35572c</anchor>
      <arglist>(const UIEVENTTYPE eventType, UIEventCallBackFn fnCallback)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VUnregisterCallBack</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a4c9f15c20f3ac04238f5338524311b67</anchor>
      <arglist>(const UIEVENTTYPE eventType)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VMoveToFront</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a762be4b2bbb3895e1c0c61057d1a7e28</anchor>
      <arglist>(const IBaseControl *const pControl)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual float</type>
      <name>VGetWidth</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>aa8740f73e71015b9bd333ea5fe482b99</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual float</type>
      <name>VGetHeight</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a38197b94a2740d1ff876815302e1d8ee</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetText</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a9760adfeaa8cfac3ae6b94e81eae4814</anchor>
      <arglist>(const Base::cString &amp;strText)=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateWindowControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>ab725c2d77b29d0267616bf1bcb883473</anchor>
      <arglist>(const cWindowControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateLabelControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>af2a909d8c958ccf7a6d40cb4bc56f7e4</anchor>
      <arglist>(const cLabelControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateButtonControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a6917609d57dad06d139543157b70cb15</anchor>
      <arglist>(const cButtonControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateCheckBoxControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a6be5d34049ec66779e9bd8c403e7d922</anchor>
      <arglist>(const cCheckBoxControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateTextBoxControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>aafbcec70542529df7ceede01a6c3ea83</anchor>
      <arglist>(const cTextBoxControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateVScrollBarControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a61dcd24ff5ec700057400b72e250fe6b</anchor>
      <arglist>(const cScrollBarControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateHScrollBarControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a6f76c6226aeb685afe9ad94b5ef5a0c7</anchor>
      <arglist>(const cScrollBarControlDef &amp;def)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::ICamera</name>
    <filename>class_graphics_1_1_i_camera.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VUpdate</name>
      <anchorfile>class_graphics_1_1_i_camera.html</anchorfile>
      <anchor>ab82dbb71686fc6eb19354ae43f9c9162</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1_i_camera.html</anchorfile>
      <anchor>ae91ba450bcff64814ac84c0984a82467</anchor>
      <arglist>(const Base::cVector3 &amp;vPosition)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Base::cVector3</type>
      <name>VGetPosition</name>
      <anchorfile>class_graphics_1_1_i_camera.html</anchorfile>
      <anchor>af37ae0804817299fc81dd742ac5cb852</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetRotation</name>
      <anchorfile>class_graphics_1_1_i_camera.html</anchorfile>
      <anchor>a3e8ad610d7742ded986d70e9ea841492</anchor>
      <arglist>(const Base::cVector3 &amp;vRotation)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const D3DXMATRIX &amp;</type>
      <name>VGetViewMatrix</name>
      <anchorfile>class_graphics_1_1_i_camera.html</anchorfile>
      <anchor>a3fbd780936fb06386769cb62a93d0de5</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API ICamera *</type>
      <name>CreateCamera</name>
      <anchorfile>class_graphics_1_1_i_camera.html</anchorfile>
      <anchor>a2443d2f1777e47a4b5316222d781577c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::stUIEventCallbackParam</name>
    <filename>struct_graphics_1_1st_u_i_event_callback_param.html</filename>
    <member kind="variable">
      <type>bool</type>
      <name>bChecked</name>
      <anchorfile>struct_graphics_1_1st_u_i_event_callback_param.html</anchorfile>
      <anchor>a8c373aea95f4622388173a282d43eb47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>iThumbPos</name>
      <anchorfile>struct_graphics_1_1st_u_i_event_callback_param.html</anchorfile>
      <anchor>a352e7b4223069697d7b1cf933b1798c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strText</name>
      <anchorfile>struct_graphics_1_1st_u_i_event_callback_param.html</anchorfile>
      <anchor>a0198766c40ea49edda59c342201f3752</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cBaseControlDef</name>
    <filename>class_graphics_1_1c_base_control_def.html</filename>
    <member kind="variable">
      <type>Base::cVector2</type>
      <name>vPosition</name>
      <anchorfile>class_graphics_1_1c_base_control_def.html</anchorfile>
      <anchor>a7fea40380c730476237e46697605b21b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cVector2</type>
      <name>vSize</name>
      <anchorfile>class_graphics_1_1c_base_control_def.html</anchorfile>
      <anchor>ab900830454a9c70606ef1eb0e3bb09ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strControlName</name>
      <anchorfile>class_graphics_1_1c_base_control_def.html</anchorfile>
      <anchor>a895758bd777a60c00026e1283e368568</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cWindowControlDef</name>
    <filename>class_graphics_1_1c_window_control_def.html</filename>
    <base>Graphics::cBaseControlDef</base>
    <member kind="enumeration">
      <name>WINDOWTYPE</name>
      <anchorfile>class_graphics_1_1c_window_control_def.html</anchorfile>
      <anchor>a59376e6f17ecb5a2380d96923c1cc914</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>WT_DESKTOP</name>
      <anchorfile>class_graphics_1_1c_window_control_def.html</anchorfile>
      <anchor>a59376e6f17ecb5a2380d96923c1cc914a5fea2cb37eae3c19c835b19153ed7e37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>WT_STANDARD</name>
      <anchorfile>class_graphics_1_1c_window_control_def.html</anchorfile>
      <anchor>a59376e6f17ecb5a2380d96923c1cc914ae614500c25efc723bc4381b56c27fbe5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WINDOWTYPE</type>
      <name>wType</name>
      <anchorfile>class_graphics_1_1c_window_control_def.html</anchorfile>
      <anchor>ad8013016c0d3bd1ed854e8815b640933</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strBGImageFile</name>
      <anchorfile>class_graphics_1_1c_window_control_def.html</anchorfile>
      <anchor>ac65aa9fe94d0e22d319f91186a5983d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>bAllowMovingControls</name>
      <anchorfile>class_graphics_1_1c_window_control_def.html</anchorfile>
      <anchor>a16e3b5dac73b9c7d965ce057c8e975a7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cLabelControlDef</name>
    <filename>class_graphics_1_1c_label_control_def.html</filename>
    <base>Graphics::cBaseControlDef</base>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strFont</name>
      <anchorfile>class_graphics_1_1c_label_control_def.html</anchorfile>
      <anchor>a5facd40da202d6c9cbfebc0ad338db57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cColor</type>
      <name>textColor</name>
      <anchorfile>class_graphics_1_1c_label_control_def.html</anchorfile>
      <anchor>a8b293325b606bc23e43c1c9848e30f9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strText</name>
      <anchorfile>class_graphics_1_1c_label_control_def.html</anchorfile>
      <anchor>abee43b30143bbf6910a9ed2242cc617d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strBGImageFile</name>
      <anchorfile>class_graphics_1_1c_label_control_def.html</anchorfile>
      <anchor>a3a157c9b4699caaabdcfb1ce00e4360d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>fTextHeight</name>
      <anchorfile>class_graphics_1_1c_label_control_def.html</anchorfile>
      <anchor>a9734dd60a53fbc9cfcdd93ebb36e7075</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>bAutoSize</name>
      <anchorfile>class_graphics_1_1c_label_control_def.html</anchorfile>
      <anchor>a873452c981c4fd8cd468a3791c0bd93a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::cButtonControlDef</name>
    <filename>struct_graphics_1_1c_button_control_def.html</filename>
    <base>Graphics::cBaseControlDef</base>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strDefaultImage</name>
      <anchorfile>struct_graphics_1_1c_button_control_def.html</anchorfile>
      <anchor>a457acddab4b6aef91b6f7bae1bba00a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strPressedImage</name>
      <anchorfile>struct_graphics_1_1c_button_control_def.html</anchorfile>
      <anchor>aadfce136efb087a1a4dcb5d74607bc1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cLabelControlDef</type>
      <name>labelControlDef</name>
      <anchorfile>struct_graphics_1_1c_button_control_def.html</anchorfile>
      <anchor>a17b0e91808f910c5ce939068ceb4f5fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>bAutoSize</name>
      <anchorfile>struct_graphics_1_1c_button_control_def.html</anchorfile>
      <anchor>a2b5110793ada12467f021776bb2e09d4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cCheckBoxControlDef</name>
    <filename>class_graphics_1_1c_check_box_control_def.html</filename>
    <base>Graphics::cBaseControlDef</base>
    <member kind="variable">
      <type>cButtonControlDef</type>
      <name>buttonControlDef</name>
      <anchorfile>class_graphics_1_1c_check_box_control_def.html</anchorfile>
      <anchor>adc08e0aeab796c54c18413cfe3e5a3d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cLabelControlDef</type>
      <name>labelControlDef</name>
      <anchorfile>class_graphics_1_1c_check_box_control_def.html</anchorfile>
      <anchor>a8c568d30b3ea8dbd0654f8d3fbd8e414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>iSpaceCaption</name>
      <anchorfile>class_graphics_1_1c_check_box_control_def.html</anchorfile>
      <anchor>a111c77b344adf0ac36a9303e991e7dd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>bChecked</name>
      <anchorfile>class_graphics_1_1c_check_box_control_def.html</anchorfile>
      <anchor>a7a79bbc8f2a5d577b9d0101e727aa61f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cTextBoxControlDef</name>
    <filename>class_graphics_1_1c_text_box_control_def.html</filename>
    <base>Graphics::cBaseControlDef</base>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strBGImage</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>a8334c90b70694e0b421af391b75d0e8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strFont</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>a9386bb828e6667d3d0d71b6803130db7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cColor</type>
      <name>textColor</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>afed3816c1cc27cc3ca8480d086d90b18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>fTextHeight</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>a219d668b7772f3362279895fd74541cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strCaretImage</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>adb449a1b95e0a095bb54b4531fc9c4ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>iCaretWidth</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>a26a20315e54b40d026e40f6e438e1628</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>fCaretUpdateTime</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>ae4ec3a55ee1d5228c1099b4549ddc0b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strText</name>
      <anchorfile>class_graphics_1_1c_text_box_control_def.html</anchorfile>
      <anchor>a95d85d55de5b5abd1b5054f7c6ba7c3f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cScrollBarControlDef</name>
    <filename>class_graphics_1_1c_scroll_bar_control_def.html</filename>
    <base>Graphics::cBaseControlDef</base>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strBGImage</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control_def.html</anchorfile>
      <anchor>aa709128b510abd6999546bfd4460f503</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cButtonControlDef</type>
      <name>thumbBtnDef</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control_def.html</anchorfile>
      <anchor>a0fd8084cb5619826ea6d5f4f3aeacd4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cButtonControlDef</type>
      <name>TopLeftArrowDef</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control_def.html</anchorfile>
      <anchor>a8bf2dfb5e3bcb6c508a3b5c0ff2c9da2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cButtonControlDef</type>
      <name>BottomRightArrowDef</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control_def.html</anchorfile>
      <anchor>a5c505ebd2cb120bdea2cd4db8e3d899a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>iMinPos</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control_def.html</anchorfile>
      <anchor>a0bede11a8177c1fbbda51b6d6dadf308</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>iMaxPos</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control_def.html</anchorfile>
      <anchor>ae719ebd7c47aa3428ff4de6d3974e135</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>iInitialThumbPosition</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control_def.html</anchorfile>
      <anchor>a88bbdb2dbb9417871de9173a320d4e2f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IGraphicsClass</name>
    <filename>class_graphics_1_1_i_graphics_class.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1_i_graphics_class.html</anchorfile>
      <anchor>a4e5ac53af27f72f2dd8c3db486582486</anchor>
      <arglist>(const HWND &amp;hWnd, const Base::cColor &amp;bkColor, const bool bFullScreen, const bool bVsyncEnabled, const int iWidth, const int iHeight, const float fScreenDepth, const float fScreenNear)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VBeginRender</name>
      <anchorfile>class_graphics_1_1_i_graphics_class.html</anchorfile>
      <anchor>a7e59dccc021f9ef91c5ac1c019623bc0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VEndRender</name>
      <anchorfile>class_graphics_1_1_i_graphics_class.html</anchorfile>
      <anchor>a100f422145823757f510db9964211aa4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetFullScreenMode</name>
      <anchorfile>class_graphics_1_1_i_graphics_class.html</anchorfile>
      <anchor>a6bb57c52f58ddf664afabafd1dd3029b</anchor>
      <arglist>(const bool bIsFullScreen)=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IGraphicsClass *</type>
      <name>GetInstance</name>
      <anchorfile>class_graphics_1_1_i_graphics_class.html</anchorfile>
      <anchor>a3966f915da04613bc5c9f62b2b7b6db6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API void</type>
      <name>Destroy</name>
      <anchorfile>class_graphics_1_1_i_graphics_class.html</anchorfile>
      <anchor>a5f6c4ee4299830a27ac9a0dc9d43cb99</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IKeyboardHandler</name>
    <filename>class_graphics_1_1_i_keyboard_handler.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VOnKeyDown</name>
      <anchorfile>class_graphics_1_1_i_keyboard_handler.html</anchorfile>
      <anchor>a3765b8ba9006294aba8e3ca1153c55df</anchor>
      <arglist>(const unsigned int iCharID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VOnKeyUp</name>
      <anchorfile>class_graphics_1_1_i_keyboard_handler.html</anchorfile>
      <anchor>ad663e5e4b3e1f1f1dbd4530b4053106b</anchor>
      <arglist>(const unsigned int iCharID)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VOnCharPress</name>
      <anchorfile>class_graphics_1_1_i_keyboard_handler.html</anchorfile>
      <anchor>aa2c39d96f80f1325ad5d98d4da45946f</anchor>
      <arglist>(const unsigned int iCharID)=0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::stModelDef</name>
    <filename>struct_graphics_1_1st_model_def.html</filename>
    <class kind="struct">Graphics::stModelDef::stSubsetDef</class>
    <member kind="variable">
      <type>stTexVertex *</type>
      <name>pVertices</name>
      <anchorfile>struct_graphics_1_1st_model_def.html</anchorfile>
      <anchor>aecafc06f924a1b99ac691e144f8f57d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned long *</type>
      <name>pIndices</name>
      <anchorfile>struct_graphics_1_1st_model_def.html</anchorfile>
      <anchor>a1206cca8aa135b3e11f94c0c4d83d903</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iNumberOfIndices</name>
      <anchorfile>struct_graphics_1_1st_model_def.html</anchorfile>
      <anchor>a4c6dd4c9437ef3bf6a247880513095c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iNumberOfVertices</name>
      <anchorfile>struct_graphics_1_1st_model_def.html</anchorfile>
      <anchor>a9b6de63b19572b4f052c6c9e5f2d4f14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; stSubsetDef &gt;</type>
      <name>vSubsetsDef</name>
      <anchorfile>struct_graphics_1_1st_model_def.html</anchorfile>
      <anchor>af145ea6b6f2077aa23e9a78034728091</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::stModelDef::stSubsetDef</name>
    <filename>struct_graphics_1_1st_model_def_1_1st_subset_def.html</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iNumberOfIndicesinSubset</name>
      <anchorfile>struct_graphics_1_1st_model_def_1_1st_subset_def.html</anchorfile>
      <anchor>a46a8146f414aae29e0c46aa203e73f9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>iStartIndexNo</name>
      <anchorfile>struct_graphics_1_1st_model_def_1_1st_subset_def.html</anchorfile>
      <anchor>a8d06e57271552bc01b6d33332ebf600d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cString</type>
      <name>strDiffuseTextureFilename</name>
      <anchorfile>struct_graphics_1_1st_model_def_1_1st_subset_def.html</anchorfile>
      <anchor>a5ac0676c2b5f8c879495e93a43991820</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cColor</type>
      <name>diffuseColor</name>
      <anchorfile>struct_graphics_1_1st_model_def_1_1st_subset_def.html</anchorfile>
      <anchor>aa38c6f099ff8826723de377a9f7a03dc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IModel</name>
    <filename>class_graphics_1_1_i_model.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VOnInitialization</name>
      <anchorfile>class_graphics_1_1_i_model.html</anchorfile>
      <anchor>a7e6d75380ea7221deed99528c334cf42</anchor>
      <arglist>(const stModelDef &amp;def)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1_i_model.html</anchorfile>
      <anchor>a1ffb057211a8b733ebcee57ce5dae9b5</anchor>
      <arglist>(const ICamera *const pCamera)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRecalculateWorldMatrix</name>
      <anchorfile>class_graphics_1_1_i_model.html</anchorfile>
      <anchor>ab3f84b37b2ee3915e6dd0b95cef49df0</anchor>
      <arglist>(const Base::cVector3 vPosition, const Base::cVector3 vRotation, const Base::cVector3 vScale)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const Graphics::IAABB *const</type>
      <name>VGetAABB</name>
      <anchorfile>class_graphics_1_1_i_model.html</anchorfile>
      <anchor>aaa6c6756a1212b4e7bc984b09fa089ac</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1_i_model.html</anchorfile>
      <anchor>aa6228ea7bfed195a669cbfb192b37241</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IModel *</type>
      <name>CreateModel</name>
      <anchorfile>class_graphics_1_1_i_model.html</anchorfile>
      <anchor>a5617905b84dd8a38f73d0f17632b0b4f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IMouseHandler</name>
    <filename>class_graphics_1_1_i_mouse_handler.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VOnLeftMouseButtonUp</name>
      <anchorfile>class_graphics_1_1_i_mouse_handler.html</anchorfile>
      <anchor>a8209abb7392e1bd6ec48462586b529eb</anchor>
      <arglist>(const int X, const int Y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VOnLeftMouseButtonDown</name>
      <anchorfile>class_graphics_1_1_i_mouse_handler.html</anchorfile>
      <anchor>aded72dc091acc4c97f880bc231ae0e02</anchor>
      <arglist>(const int X, const int Y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VOnMouseMove</name>
      <anchorfile>class_graphics_1_1_i_mouse_handler.html</anchorfile>
      <anchor>aba2d4a74fd2769a0ea258cceaab1abba</anchor>
      <arglist>(const int X, const int Y)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IObjModelLoader</name>
    <filename>class_graphics_1_1_i_obj_model_loader.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VLoadModelFromFile</name>
      <anchorfile>class_graphics_1_1_i_obj_model_loader.html</anchorfile>
      <anchor>a7d8fd511c5d34a3962bd58d4e3730868</anchor>
      <arglist>(const Base::cString &amp;strModelFile, IModel *pModel)=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IObjModelLoader *</type>
      <name>GetInstance</name>
      <anchorfile>class_graphics_1_1_i_obj_model_loader.html</anchorfile>
      <anchor>a72be02f7d6d400874f8ce676077ec5bb</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IScreenElement</name>
    <filename>class_graphics_1_1_i_screen_element.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1_i_screen_element.html</anchorfile>
      <anchor>ac3a0a6949f8be022a6b1c5287de884db</anchor>
      <arglist>(const ICamera *const pCamera)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetVisible</name>
      <anchorfile>class_graphics_1_1_i_screen_element.html</anchorfile>
      <anchor>a7653cdf5a504bdf49dca63d0cf917071</anchor>
      <arglist>(bool bIsVisible)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::ISentence</name>
    <filename>class_graphics_1_1_i_sentence.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>a4d1290ffff2b4df85ba05b04d6580e3c</anchor>
      <arglist>(const Base::cString &amp;strFont, const Base::cString &amp;strText, const Base::cColor &amp;textColor)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>aea4c507a579278675c14da3ee65e78e8</anchor>
      <arglist>(const ICamera *const pCamera)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>a355a8cdfb14846d0f47d42124fc83047</anchor>
      <arglist>(const Base::cVector2 &amp;vPosition)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetText</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>ae7280bd0ba3353fda7d31d13e0e4fb71</anchor>
      <arglist>(const Base::cString &amp;strText)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetTextColor</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>afcba9141f984224abcb58479232ef301</anchor>
      <arglist>(const Base::cColor &amp;colorText)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual float</type>
      <name>VGetWidth</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>a0b8b14385fcb2424ee6b0ee9ff2945e7</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual float</type>
      <name>VGetWidth</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>ad4f9b5fcf738a3adbd0636c0f4ee2f89</anchor>
      <arglist>(const Base::cString &amp;strText) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VGetText</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>a68020705fd4b391fc36445faa89f7a1b</anchor>
      <arglist>(Base::cString &amp;strText) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual float</type>
      <name>VGetHeight</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>a4b77d74533450f835febb085426bba9f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetHeight</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>aee1aa81d3b480bd6d0e833d26c81f31a</anchor>
      <arglist>(const float fTextHeight)=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API ISentence *</type>
      <name>CreateSentence</name>
      <anchorfile>class_graphics_1_1_i_sentence.html</anchorfile>
      <anchor>a8fbf556e8dae0d12d853e4f00225d6b0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::ISprite</name>
    <filename>class_graphics_1_1_i_sprite.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>a63ac43c6f15561a36b6efce00a8798ee</anchor>
      <arglist>(shared_ptr&lt; ITexture &gt; const pTexture)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>aa6aa8fac777b13a28acde49767be10f1</anchor>
      <arglist>(const Base::cString &amp;strTextureFilename)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>a6f79f4f947cee7241151a8874ee0ada7</anchor>
      <arglist>(const ICamera *const pCamera)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>a2f824a69a1f80303b69238d626be5ee2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>a6824a3d60fb1fe46aa071d92ad560e74</anchor>
      <arglist>(const Base::cVector2 &amp;vPosition)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetSize</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>af0ad7531b0a473e660dfcd08e85a13b0</anchor>
      <arglist>(const Base::cVector2 &amp;vSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Base::cVector2</type>
      <name>VGetSize</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>a53e433fcfcbe9bc91ef8fcd7e9685c13</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetTexture</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>a7ddc457452e1f9dec0063cd31b5d0d8a</anchor>
      <arglist>(shared_ptr&lt; ITexture &gt; const pTexture)=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API shared_ptr&lt; ISprite &gt;</type>
      <name>CreateSprite</name>
      <anchorfile>class_graphics_1_1_i_sprite.html</anchorfile>
      <anchor>a1a20af982946194e201f6c34fcbfb72c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::stTexVertex</name>
    <filename>struct_graphics_1_1st_tex_vertex.html</filename>
    <member kind="variable">
      <type>float</type>
      <name>m_fZ</name>
      <anchorfile>struct_graphics_1_1st_tex_vertex.html</anchorfile>
      <anchor>ae68b2d4a58f059552c410e8a758fa419</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>m_fTex1</name>
      <anchorfile>struct_graphics_1_1st_tex_vertex.html</anchorfile>
      <anchor>a7a3142a9c0cbf71e12125c9fd870b72b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cBaseControl</name>
    <filename>class_graphics_1_1c_base_control.html</filename>
    <base>Graphics::IBaseControl</base>
    <base>Base::cNonCopyable</base>
    <member kind="function">
      <type>void</type>
      <name>VSetVisible</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a029e9b57875c429d5299873695df2db7</anchor>
      <arglist>(bool bIsVisible)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a14ef938172336c51243f11171ce4f48b</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VOnLeftMouseButtonUp</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>af7bc88e90720fe0bc593c906cacbb8da</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VOnLeftMouseButtonDown</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a537e14bfcb8e201a074768364f3976f2</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VOnMouseMove</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a9839b4ee4ffe72fb322fc82bb49d52c8</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VOnKeyDown</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>abbbf56e35b4b9c2bbbad9c1a36da5b0c</anchor>
      <arglist>(const unsigned int iCharID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VOnCharPress</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>adcee11e93edef3aecdf6ea09326c95df</anchor>
      <arglist>(const unsigned int iCharID)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>VAddChildControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ad0d649f5483a704f74fea7393849d5fd</anchor>
      <arglist>(shared_ptr&lt; IBaseControl &gt; pChildControl)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const Base::cVector2</type>
      <name>VGetSize</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ac442ca611bbecf9c355f65a26e7008e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>VSetSize</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a946bae4dbd4ab5ba337374ced98029f5</anchor>
      <arglist>(const Base::cVector2 &amp;vSize)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>float</type>
      <name>VGetWidth</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ac359ae0c6b3d07289b8c4cacbce4d893</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>float</type>
      <name>VGetHeight</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ad015ae25a141d1fd88d16dac439310fc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>abd89b36bb84608bad251ba77d7ee47cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VOnFocusChanged</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a0f8b36f8b76ebfdaf5c91d1f70c17f20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ac27214d5202e70ff4a2613b43f1ee398</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetFocusControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ac20aeffc85ece4a19d5476a296326336</anchor>
      <arglist>(const cBaseControl *const pControl)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetFocus</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a6fcbd5705e1625f5b37106120b52fe00</anchor>
      <arglist>(const bool bFocus)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>UIEventCallBackFn *</type>
      <name>GetCallbackFromMap</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a83ce1e27a5d6be22758b55163283222b</anchor>
      <arglist>(const UIEVENTTYPE eventType)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>shared_ptr&lt; ISprite &gt;</type>
      <name>m_pBGSprite</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ac4a1bfbfd5d0008dc133acef5badef0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Base::cVector2</type>
      <name>m_vControlAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>aa88faaae95676a28f70d4758a59aab73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Base::cVector2</type>
      <name>m_vSize</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a1df7cb87dfb3d227b6ff7155d34bc407</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_bFocus</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>af0a000d0d80efb0e85d1501ae711c24c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_bAllowMovingControls</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ae6b364e58a8ad61910ebbcf554d0b200</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Base::cVector2</type>
      <name>m_vPosition</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a3d3dd1617c86a189d864c9083b503f11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_bIsLeftMouseDown</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a08ad97ff28c6b833c224259ae6d9cc86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>UIEventCallBackMap</type>
      <name>m_CallbackMap</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ae6a5f3422bc5bab5b7da756eccec0173</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ControlList</type>
      <name>m_pChildControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ae5782a9cd86a6dfc80744f8567237aea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_bVisible</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a7a96603c3106843eb546b0970c784570</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::list&lt; shared_ptr&lt; cBaseControl &gt; &gt;</type>
      <name>ControlList</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a7fe4efaf5a36680c52083c8bf036f08d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; UIEVENTTYPE, UIEventCallBackFn &gt;</type>
      <name>UIEventCallBackMap</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a4eba34c33b373e1c504327de2b929f16</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnKeyUp</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a29808193633ea4676e5c944f46621970</anchor>
      <arglist>(const unsigned int iCharID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VPostMsg</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>abc952ce5b38161adf7c433727bace01f</anchor>
      <arglist>(const Base::AppMsg &amp;msg)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRemoveAllChildren</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a468d45da22f190937589713d2fa7e6ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRemoveChildControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ade22b4930c24b7f380302b783519e36e</anchor>
      <arglist>(const Base::cString &amp;strControlName)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Graphics::IBaseControl *const</type>
      <name>VFindChildControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a04478580b669cfd0414d7cc19b715cd2</anchor>
      <arglist>(const Base::cString &amp;strControlName)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetText</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a514be165ce7e316dee8646cb127ed628</anchor>
      <arglist>(const Base::cString &amp;strText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ad3308bbe1db961bfc25fa51cbbf7c72e</anchor>
      <arglist>(const Base::cVector2 &amp;vPosition)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRegisterCallBack</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a4b6a62fbc6a894cf12f97e7dc38ca191</anchor>
      <arglist>(const UIEVENTTYPE eventType, UIEventCallBackFn fnCallback)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VUnregisterCallBack</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>aab8601ab1dd21eb4bf3b9691be1b61db</anchor>
      <arglist>(const UIEVENTTYPE eventType)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VMoveToFront</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a11eb61dcc357858555a850d386ffbfe2</anchor>
      <arglist>(const IBaseControl *const pControl)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>AllowMovingControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a908dbb7f5c8aaf9a25e8f8247ed1e269</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ConstrainChildControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>aee0123db99bd97247085a209eca0d983</anchor>
      <arglist>(float &amp;fX, float &amp;fY)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetParentControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ad8a8b2d33585acb7063a4cf435047111</anchor>
      <arglist>(cBaseControl *pParentControl)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>PostToAll</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>aac3c6b00b5f338c4265826b0bc0591ab</anchor>
      <arglist>(const Base::AppMsg &amp;msg)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsCursorIntersect</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>aac51bbd96c5ae6c775de5a15bdb3e4a1</anchor>
      <arglist>(const float fX, const float fY)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ControlList::const_iterator</type>
      <name>GetChildControlIterator</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>ad8e16281d14e4366d5bdfd10b97b38b7</anchor>
      <arglist>(const IBaseControl *const pChildControl)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>cBaseControl *</type>
      <name>m_pFocusControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a3bedc44b53a4921e2fb8bb80318a5dac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>cBaseControl *</type>
      <name>m_pParentControl</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a07dde29ed8077f1189165fca6761a0a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iMouseDownXPos</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a6e765e6a0b11f68f89d9ee2a46ed2dc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iMouseDownYPos</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a1e9ecc743879665df5e2eb6d67cdb16b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cHashedString</type>
      <name>m_strControlName</name>
      <anchorfile>class_graphics_1_1c_base_control.html</anchorfile>
      <anchor>a437865375738c5cf897614c18395f057</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cBaseShader</name>
    <filename>class_graphics_1_1c_base_shader.html</filename>
    <base>Graphics::IShader</base>
    <base>Base::cNonCopyable</base>
    <class kind="struct">Graphics::cBaseShader::MatrixBufferType</class>
    <member kind="function">
      <type>void</type>
      <name>VSetTexture</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a8847a68f7a01fbe80ac213f301a35a9c</anchor>
      <arglist>(shared_ptr&lt; ITexture &gt; pTexture)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a532e7425b137104d8cf187411356c89d</anchor>
      <arglist>(const D3DXMATRIX &amp;inMatWorld, const D3DXMATRIX &amp;inMatView, const D3DXMATRIX &amp;inMatProjection)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>ac191c6bb661c6e2bc3a7a31d560a4f76</anchor>
      <arglist>(const Base::cString &amp;strShaderName)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VSetShaderParameters</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>ac8393cd0e7982d75cbab1f9044f392a8</anchor>
      <arglist>(const D3DXMATRIX &amp;inMatWorld, const D3DXMATRIX &amp;inMatView, const D3DXMATRIX &amp;inMatProjection)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VRenderShader</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a5d1c97cbe53a0cd3ff5e8bc36efb7510</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a7f49439b7d3cf52a58d27a6a2bc57d9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ID3D11InputLayout *</type>
      <name>m_pLayout</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a6b9a61f6407ec121361d5d5e461b855d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>shared_ptr&lt; ITexture &gt;</type>
      <name>m_pTexture</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>aed81100b8f8c58aa9143b0359319344d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual bool</type>
      <name>VCreateLayout</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a7df743b698e7f9e9af825a8b4e1aac0e</anchor>
      <arglist>(shared_ptr&lt; Utilities::IResHandle const  &gt; shaderHandle)=0</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateVertexShader</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a996e26cc37d1a61fd4d756492aba9a72</anchor>
      <arglist>(const Base::cString &amp;strShaderName)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreatePixelShader</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a3e69d02d3184d6c0090445e18436b72c</anchor>
      <arglist>(const Base::cString &amp;strShaderName)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11VertexShader *</type>
      <name>m_pVertexShader</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a12cadce8c9828bae1f4df33e0067f271</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11PixelShader *</type>
      <name>m_pPixelShader</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>afdfffa726f5b0825e1e5a0caa42c3863</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11Buffer *</type>
      <name>m_pMatrixBuffer</name>
      <anchorfile>class_graphics_1_1c_base_shader.html</anchorfile>
      <anchor>a8e7b20144e8f93f0d756c7d631f15483</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::cBaseShader::MatrixBufferType</name>
    <filename>struct_graphics_1_1c_base_shader_1_1_matrix_buffer_type.html</filename>
    <member kind="variable">
      <type>D3DXMATRIX</type>
      <name>world</name>
      <anchorfile>struct_graphics_1_1c_base_shader_1_1_matrix_buffer_type.html</anchorfile>
      <anchor>ab4f1eb0e4d0149e1da9fc9f1f65ea1cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>D3DXMATRIX</type>
      <name>view</name>
      <anchorfile>struct_graphics_1_1c_base_shader_1_1_matrix_buffer_type.html</anchorfile>
      <anchor>a0e05234f796f6adb3ea73b498c898e47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>D3DXMATRIX</type>
      <name>projection</name>
      <anchorfile>struct_graphics_1_1c_base_shader_1_1_matrix_buffer_type.html</anchorfile>
      <anchor>abaa1650525c7217b6dfd1ff425a25733</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cButtonControl</name>
    <filename>class_graphics_1_1c_button_control.html</filename>
    <base>Graphics::cBaseControl</base>
    <member kind="function">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>acb86d8df674457ea630ebf55f6845668</anchor>
      <arglist>(const cButtonControlDef &amp;def)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>a795ba8ac277800aed7f2dff9319ae44a</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnLeftMouseButtonUp</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>a0d3c255b6820098c02b8cd28b459cf87</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnLeftMouseButtonDown</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>a8a4c004a0e06764ba839ca37935e20b3</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>abb8dc3843321029ee9a75ded4e249411</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; ITexture &gt;</type>
      <name>m_pDefaultTexture</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>ad658a2020e79aa37fe52a8419100fedb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; ITexture &gt;</type>
      <name>m_pPressedTexture</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>a47d37690bdf5f5fe717e5bc7c0d204d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; IBaseControl &gt;</type>
      <name>m_pLabel</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>a17d6e184388733636786d3dff36e7f0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bPressed</name>
      <anchorfile>class_graphics_1_1c_button_control.html</anchorfile>
      <anchor>a27902bd6481c6b94d4778ff905d4cc93</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cCamera</name>
    <filename>class_graphics_1_1c_camera.html</filename>
    <base>Graphics::ICamera</base>
    <base>Base::cNonCopyable</base>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VUpdate</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>a2a343cf4b60b782e6aa20ff8dbb00d30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Base::cVector3</type>
      <name>VGetPosition</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>a92ddfc0410ba24d97d5f69f891758a4c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>a84f88e2c16eaf934f83f305cff751e8f</anchor>
      <arglist>(const Base::cVector3 &amp;vPosition)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const D3DXMATRIX &amp;</type>
      <name>VGetViewMatrix</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>a55e27f64b8fadb1bf0ff4e8659864598</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetRotation</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>a60faee0d75121355ba9bd6e16de079d7</anchor>
      <arglist>(const Base::cVector3 &amp;vRotation)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CalculateViewMatrix</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>a7fdacef05e32e7e77d9d7167ebcf86b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cVector3</type>
      <name>m_vPosition</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>adb1a020d5209eff0219c92cf5f3aadae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cVector3</type>
      <name>m_vRotation</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>af388adc743fb6317850addd8be870a5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DXMATRIX</type>
      <name>m_matView</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>aa3a1e779af3048cd691524736d4dcc57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bIsDirty</name>
      <anchorfile>class_graphics_1_1c_camera.html</anchorfile>
      <anchor>a94c3ce7ecfd99716ed4f5b6c3a5013e7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cCheckBoxControl</name>
    <filename>class_graphics_1_1c_check_box_control.html</filename>
    <base>Graphics::cBaseControl</base>
    <member kind="function">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>class_graphics_1_1c_check_box_control.html</anchorfile>
      <anchor>a81a64ac98e064832ccb61cebf8ddf50a</anchor>
      <arglist>(const cCheckBoxControlDef &amp;def)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_check_box_control.html</anchorfile>
      <anchor>aaaf722d2ffa67546a139496e7c0e1887</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnLeftMouseButtonDown</name>
      <anchorfile>class_graphics_1_1c_check_box_control.html</anchorfile>
      <anchor>ae5b6267d1638b48296efe61c2bdcde1b</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_check_box_control.html</anchorfile>
      <anchor>a18aa91f2f0dbec3f6739bb821b860b77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bChecked</name>
      <anchorfile>class_graphics_1_1c_check_box_control.html</anchorfile>
      <anchor>ac2ed545a7128ae3eacc699a7f1436acb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; IBaseControl &gt;</type>
      <name>m_pTickBox</name>
      <anchorfile>class_graphics_1_1c_check_box_control.html</anchorfile>
      <anchor>a20cda7a422c8b25cddb8f97d5d80917d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cColorShader</name>
    <filename>class_graphics_1_1c_color_shader.html</filename>
    <base>Graphics::cBaseShader</base>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VCreateLayout</name>
      <anchorfile>class_graphics_1_1c_color_shader.html</anchorfile>
      <anchor>aca4793c50ce50f9ab415bba648845e20</anchor>
      <arglist>(shared_ptr&lt; Utilities::IResHandle const  &gt; shaderHandle)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cDXBase</name>
    <filename>class_graphics_1_1c_d_x_base.html</filename>
    <base>Graphics::IDXBase</base>
    <base>Base::cNonCopyable</base>
    <member kind="function" static="yes">
      <type>static IDXBase *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a005171a0127b4a5db45c5ee104755b0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static IDXBase *</type>
      <name>s_pDXBase</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a66b92901af2f6d4d64f055d5e0fb714d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a961dd6fe10b9f869d7b305034fd057dc</anchor>
      <arglist>(const HWND &amp;hWnd, const Base::cColor &amp;bkColor, const bool bFullScreen, const bool bVsyncEnabled, const int iWidth, const int iHeight, const float fScreenDepth, const float fScreenNear)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VBeginRender</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a90d2de1d9eb9533b65e647d715205a05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VEndRender</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aff40cd5965d13b438c36b6eca7e5f92c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VTurnZBufferOn</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a6e97e6bd69332e81989579bb8ab1fcdc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VTurnZBufferOff</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a1e4eeb54924566538f91abd4e5db1267</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VTurnOnAlphaBlending</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a05e29521ac0431b10d35f770590ccda5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VTurnOffAlphaBlending</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a38f29712f903d54a9d49ab6309842b4a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetFullScreenMode</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aad4398de354c6bb4c85bdd8ec3be6235</anchor>
      <arglist>(const bool bIsFullScreen)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ID3D11Device *</type>
      <name>VGetDevice</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ac581c75376545845119f9486ab69dbd1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>ID3D11DeviceContext *</type>
      <name>VGetDeviceContext</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a5ce9bf766a355f6158f50f8dfcea5d80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>const D3DMATRIX &amp;</type>
      <name>VGetWorldMatrix</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aedb2f8ac7d52dc8f8ffba57bd43c5101</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>const D3DMATRIX &amp;</type>
      <name>VGetProjectionMatrix</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a47438631fbfe54998a2e964d4f53cdd8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>const D3DMATRIX &amp;</type>
      <name>VGetOrthoMatrix</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a2971a6fb79e54b06ce20183906383d12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>VGetScreenWidth</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a5897d6c905518fbe67303d3be6321c3b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>VGetScreenHeight</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ad677f33bfafe7c811ff10e71eeca1db6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>SetupRenderTargets</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a28a8fddce34a60ab1a228cdbcea4016e</anchor>
      <arglist>(const int iWidth, const int iHeight, const HWND &amp;hWnd, const bool bFullScreen)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>SetupSwapChain</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a7e919a35ffb203d1be359fab1a5453c2</anchor>
      <arglist>(const int iWidth, const int iHeight, const HWND &amp;hWnd, const bool bFullScreen)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>SetupDepthStencilStateFor3D</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>abd66ed1b3f91fabd164233d68304cb07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>SetupDepthStencilStateFor2D</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a6e3a1cb1e5862a2491a17307ca6be436</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateBlendStates</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aa1e8c9c28f3f7273eddb14e5a172662b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>SetupRasterStates</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a673568a45eb0f6bf10467c993e5d5b69</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetupViewPort</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a403c49a56be4f2542a8f54bb25f7c3be</anchor>
      <arglist>(const int iWidth, const int iHeight)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetDisplayMode</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a8c351b2203931cd06a1d7f79e5237afe</anchor>
      <arglist>(const int iWidth, const int iHeigh)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>AttachBackBufferToSwapChain</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>adc3154595b000d94a88b94bab03dcd3b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateDepthStencilBuffer</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a01f834f8550cef456e9abd4d8b6206ca</anchor>
      <arglist>(const int iWidth, const int iHeight)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateDepthStencilView</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a85f4207c95d3bb3bd67ff764cac9da90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetupProjectionMatrix</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a76871a279809b44712fd9f8daf340ae1</anchor>
      <arglist>(const int iWidth, const int iHeight, const float fScreenNear, const float fScreenDepth)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Cleanup</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a9c33adf605f82264e1bfe0c676be2a58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bVsyncEnabled</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a6981fda9bf333b7b9b0eef9207ddbc7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>IDXGISwapChain *</type>
      <name>m_pSwapChain</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a94cc23410fb420c549e2419e4c407318</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11Device *</type>
      <name>m_pDevice</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ae8e395a27737ac88d4b45d812cc6b773</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11DeviceContext *</type>
      <name>m_pDeviceContext</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ab303af36a5a11e0718658e4c1f45e722</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11RenderTargetView *</type>
      <name>m_pRenderTargetView</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aea18216b6857bb42a737e03f3881d273</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11Texture2D *</type>
      <name>m_pDepthStencilBuffer</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ae27ba5cd8dd133be41ed218120f61599</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11DepthStencilState *</type>
      <name>m_p3DDepthStencilState</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ad4bab4a92b632442eb82560e8652706f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11DepthStencilState *</type>
      <name>m_p2DDepthStencilState</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a044ccfaf66549d2c8b0714bdad556758</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11DepthStencilView *</type>
      <name>m_pDepthStencilView</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aa69051ed9b0c0f613839f58b3bb68d26</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11RasterizerState *</type>
      <name>m_pRasterState</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a2afe8d255d1d031e1a64de5f39e0b330</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DXMATRIX</type>
      <name>m_matProjection</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a711b9296863e953ff67fe140eff6ab4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DXMATRIX</type>
      <name>m_matWorld</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a70727dce4d20c97c1ac03af75519a4da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DXMATRIX</type>
      <name>m_matOrtho</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ac8658f2372b5d9e4085f3acda326be8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_afBackGroundcolor</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ae9fe761e3392c129759e2bb83505d211</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iScreenWidth</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ae8b0de5299f0cd821bb33df398e4d269</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iScreenHeight</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a59ff764a6c819808450a73e53aeebaba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11BlendState *</type>
      <name>m_pAlphaEnableBlendingState</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a4c1e9ddd3fc98639d949e2ea0ad62ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11BlendState *</type>
      <name>m_pAlphaDisableBlendingState</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a7f7900eb3c0aa45cc57ff70c84cbdee4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IDXBase</name>
    <filename>class_graphics_1_1_i_d_x_base.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>af98e6eb2096764e985205a6798daf31f</anchor>
      <arglist>(const HWND &amp;hWnd, const Base::cColor &amp;bkColor, const bool bFullScreen, const bool bVsyncEnabled, const int iWidth, const int iHeight, const float fScreenDepth, const float fScreenNear)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VBeginRender</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a73b883af483302998f09894eb0ac65ba</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VEndRender</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>ac45a3ada673523b0fb56a6036ffed48d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VTurnZBufferOn</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a0e86320f8a6e14c9ec792790064d898a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VTurnZBufferOff</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a7820b17190bd62cfe59b89a7e015e463</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VTurnOnAlphaBlending</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>af54f1fc726c1faaac9c926d7ec09e33b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VTurnOffAlphaBlending</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>ab30df4ed21cde68581e53e68ad2d0824</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ID3D11Device *</type>
      <name>VGetDevice</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>af7747ce703fcdfc486b2700453620e49</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ID3D11DeviceContext *</type>
      <name>VGetDeviceContext</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>aba1c402572418f842b0381f1e52de2c8</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const D3DMATRIX &amp;</type>
      <name>VGetWorldMatrix</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a9f77368af10ff99741853214a30bcfd4</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const D3DMATRIX &amp;</type>
      <name>VGetProjectionMatrix</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a2aa7505860dae2fb9c6ae8cb97f162dc</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const D3DMATRIX &amp;</type>
      <name>VGetOrthoMatrix</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a81bcc7dfae165e1d8b604146b81fcc77</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>VGetScreenWidth</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a5d4f711a00976ca9c4c4d0654f5b8f47</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>VGetScreenHeight</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a7c0edd174ad2ddd736f0a7e0239e52d2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetFullScreenMode</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>af0451d22437c39e0cf292c465c7c3562</anchor>
      <arglist>(const bool bIsFullScreen)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cMyFont</name>
    <filename>class_graphics_1_1c_my_font.html</filename>
    <base protection="private">Base::cNonCopyable</base>
    <member kind="typedef" protection="private">
      <type>std::map&lt; int, const CharDescriptor &gt;</type>
      <name>CharDescriptorMap</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>ac2b06804b35bc56569331daeb6622540</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ParseFontDesc</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>af81cfeb404c5d739bc243635b30c673d</anchor>
      <arglist>(const Base::cString &amp;strFontDescFilename)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>InitializeShader</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>a0f5ebd004a6f4baaa2156e7c6c1ed250</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Cleanup</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>ab14281ecd1bf1663534ae64c517367b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; cFontShader &gt;</type>
      <name>m_pShader</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>a418303b3358d6ef47da3676a5cbb8462</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; ITexture &gt;</type>
      <name>m_pTexture</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>a7bc48906e3a091f456fad1daf46c0fd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cString</type>
      <name>m_strFontTexPath</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>aba3bd2a9e47fba9718add1499e921ce2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iTextureWidth</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>a628112b619e270d96217e2c5fce16d79</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iTextureHeight</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>a56abd2d1e33d53c38490583ad9caeef7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>CharDescriptorMap</type>
      <name>m_CharDescriptorMap</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>a82a5bfb84ddce4231137363558921546</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iFontHeight</name>
      <anchorfile>class_graphics_1_1c_my_font.html</anchorfile>
      <anchor>aa942e1cfff4b0ff02903908a79643fea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::IMyFont::CharDescriptor</name>
    <filename>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</filename>
    <member kind="variable">
      <type>unsigned short</type>
      <name>id</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>a3374489c898614b7f7a0765c66ffe3b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>x</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>af7f820ba956a52a3af5e8682f82ac2c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>y</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>a383ca50892e796a1dda7c73c577ce5e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>Width</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>a9a7c8313e477a843b057badd2e698ee2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>Height</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>adda9929cf4e9b724253a538ed0375bf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>XOffset</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>a8ead2af52423d1493f96135c60722009</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>YOffset</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>a73091fd92c7324c9b77ae7c7cae471e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned short</type>
      <name>XAdvance</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1_char_descriptor.html</anchorfile>
      <anchor>a897e85f8d726a5684760220e671cabfb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::IMyFont::stVertexData</name>
    <filename>struct_graphics_1_1_i_my_font_1_1st_vertex_data.html</filename>
    <member kind="variable">
      <type>CharDescriptor</type>
      <name>ch</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1st_vertex_data.html</anchorfile>
      <anchor>ac1794a66ae0ae0959288d76fcafcffa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>fTexU</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1st_vertex_data.html</anchorfile>
      <anchor>a9aacf9189425807d0b8a0975106c3da5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>fTexV</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1st_vertex_data.html</anchorfile>
      <anchor>a63c5e22544f47e9fecea4758f99be67e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>fTexU1</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1st_vertex_data.html</anchorfile>
      <anchor>af0876ca72ffed06b2ab2677e6a3122ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>fTexV1</name>
      <anchorfile>struct_graphics_1_1_i_my_font_1_1st_vertex_data.html</anchorfile>
      <anchor>a0584cf3a207671111940861c9ec1a9a7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cFontManager</name>
    <filename>class_graphics_1_1c_font_manager.html</filename>
    <base>Graphics::IFontManager</base>
    <member kind="function" static="yes">
      <type>static IFontManager *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_font_manager.html</anchorfile>
      <anchor>a4643dce4eaf181b9c5b69225584096a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static IFontManager *</type>
      <name>s_pFontManager</name>
      <anchorfile>class_graphics_1_1c_font_manager.html</anchorfile>
      <anchor>afbbf04f35cec324e69ee147a223baafe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; unsigned long, shared_ptr&lt; IMyFont &gt; &gt;</type>
      <name>FontMap</name>
      <anchorfile>class_graphics_1_1c_font_manager.html</anchorfile>
      <anchor>a937e7d0a6a0e9546c65c05009c2dbbda</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>shared_ptr&lt; IMyFont &gt;</type>
      <name>VGetFont</name>
      <anchorfile>class_graphics_1_1c_font_manager.html</anchorfile>
      <anchor>a9dee90ce65e79485a532efc7dac64440</anchor>
      <arglist>(const Base::cString &amp;strFontName)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>shared_ptr&lt; IMyFont &gt;</type>
      <name>Find</name>
      <anchorfile>class_graphics_1_1c_font_manager.html</anchorfile>
      <anchor>a11d910ea95800181c3f2164a83dd4326</anchor>
      <arglist>(const unsigned long ulFontHash)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>FontMap</type>
      <name>m_pFonts</name>
      <anchorfile>class_graphics_1_1c_font_manager.html</anchorfile>
      <anchor>a6c23fa0329742d736284177f368d923c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IFontManager</name>
    <filename>class_graphics_1_1_i_font_manager.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual shared_ptr&lt; IMyFont &gt;</type>
      <name>VGetFont</name>
      <anchorfile>class_graphics_1_1_i_font_manager.html</anchorfile>
      <anchor>a841ec21d29af707f38a2601f1fee1cce</anchor>
      <arglist>(const Base::cString &amp;strFontName)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cFontShader</name>
    <filename>class_graphics_1_1c_font_shader.html</filename>
    <base>Graphics::cTextureShader</base>
    <class kind="struct">Graphics::cFontShader::PixelBufferType</class>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetShaderParameters</name>
      <anchorfile>class_graphics_1_1c_font_shader.html</anchorfile>
      <anchor>a9c6157f1612771618cd7e1e5895e19a1</anchor>
      <arglist>(const D3DXMATRIX &amp;inMatWorld, const D3DXMATRIX &amp;inMatView, const D3DXMATRIX &amp;inMatProjection)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::cFontShader::PixelBufferType</name>
    <filename>struct_graphics_1_1c_font_shader_1_1_pixel_buffer_type.html</filename>
    <member kind="variable">
      <type>D3DXVECTOR4</type>
      <name>pixelColor</name>
      <anchorfile>struct_graphics_1_1c_font_shader_1_1_pixel_buffer_type.html</anchorfile>
      <anchor>adb6a480b37dfa7a60fed07c905e2439d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cGraphicsClass</name>
    <filename>class_graphics_1_1c_graphics_class.html</filename>
    <base>Graphics::IGraphicsClass</base>
    <base>Base::cNonCopyable</base>
    <member kind="function">
      <type>void</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1c_graphics_class.html</anchorfile>
      <anchor>a8bebe05308344ef4479881fbb5ca1ab0</anchor>
      <arglist>(const HWND &amp;hWnd, const Base::cColor &amp;bkColor, const bool bFullScreen, const bool bVsyncEnabled, const int iWidth, const int iHeight, const float fScreenDepth, const float fScreenNear)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VBeginRender</name>
      <anchorfile>class_graphics_1_1c_graphics_class.html</anchorfile>
      <anchor>afc917905a44c632b7de0e3d4b96e4f4e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VEndRender</name>
      <anchorfile>class_graphics_1_1c_graphics_class.html</anchorfile>
      <anchor>ad9fcbff3fb12ed855ac070bc9c9c00a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VSetFullScreenMode</name>
      <anchorfile>class_graphics_1_1c_graphics_class.html</anchorfile>
      <anchor>a30674f2077f6383f4f6b748b46b913b8</anchor>
      <arglist>(const bool bIsFullScreen)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Cleanup</name>
      <anchorfile>class_graphics_1_1c_graphics_class.html</anchorfile>
      <anchor>ae3c2fae05ba1eafdb8f78b9ca937c93f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IGraphicsClass *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_graphics_class.html</anchorfile>
      <anchor>a81a4c7efee5f7d59c511a7571e48986b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static IGraphicsClass *</type>
      <name>s_pGraphic</name>
      <anchorfile>class_graphics_1_1c_graphics_class.html</anchorfile>
      <anchor>a1604e6cbd4dbd626c9778a0a5d47af50</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cHScrollBar</name>
    <filename>class_graphics_1_1c_h_scroll_bar.html</filename>
    <base>Graphics::cScrollBarControl</base>
    <member kind="function" static="yes">
      <type>static cHScrollBar *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_h_scroll_bar.html</anchorfile>
      <anchor>a777eeab213c1b05f51d5f70b5b2683d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnMouseMove</name>
      <anchorfile>class_graphics_1_1c_h_scroll_bar.html</anchorfile>
      <anchor>a81504a6a578bf4ea458d496e38b1b019</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_h_scroll_bar.html</anchorfile>
      <anchor>aed6f005d397791f292b387442e4935a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetSize</name>
      <anchorfile>class_graphics_1_1c_h_scroll_bar.html</anchorfile>
      <anchor>a5971c0ab656027e6590a572f0b6b4b85</anchor>
      <arglist>(const Base::cVector2 &amp;vSize)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetThumbPosition</name>
      <anchorfile>class_graphics_1_1c_h_scroll_bar.html</anchorfile>
      <anchor>aee4a4d3bfa0816bfbcd34630b6166122</anchor>
      <arglist>(const int iNewPosition)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>AutoSizeThumb</name>
      <anchorfile>class_graphics_1_1c_h_scroll_bar.html</anchorfile>
      <anchor>aacba808a882f5aee788fda873eb6db47</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cLabelControl</name>
    <filename>class_graphics_1_1c_label_control.html</filename>
    <base>Graphics::cBaseControl</base>
    <member kind="function">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>class_graphics_1_1c_label_control.html</anchorfile>
      <anchor>ab49558d14862665c2aa8fd060ffdbfbf</anchor>
      <arglist>(const cLabelControlDef &amp;def)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_label_control.html</anchorfile>
      <anchor>a3e16a5110c55f9023d5ea37c4ef93bc2</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_label_control.html</anchorfile>
      <anchor>a23f72e80fef5a630820f2ffd7dc2019f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetText</name>
      <anchorfile>class_graphics_1_1c_label_control.html</anchorfile>
      <anchor>a8bc124b0c4c2739f50db4e5626a45f17</anchor>
      <arglist>(const Base::cString &amp;strText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_label_control.html</anchorfile>
      <anchor>a74f706b47f38677c6fe1040cc456a52b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ISentence *</type>
      <name>m_pSentence</name>
      <anchorfile>class_graphics_1_1c_label_control.html</anchorfile>
      <anchor>a128b2afdbdf3566eebb5a8df22d7a4ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cModel</name>
    <filename>class_graphics_1_1c_model.html</filename>
    <base>Graphics::IModel</base>
    <base>Base::cNonCopyable</base>
    <class kind="struct">Graphics::cModel::stObjectSubset</class>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnInitialization</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>ae340e6d95d763c5f3dcc70a6d181f05f</anchor>
      <arglist>(const stModelDef &amp;def)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a0fabc763f10012590eca047256707417</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRecalculateWorldMatrix</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a9e1820c2b7293150a191aed2000f7463</anchor>
      <arglist>(const Base::cVector3 vPosition, const Base::cVector3 vRotation, const Base::cVector3 vScale)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const Graphics::IAABB *const</type>
      <name>VGetAABB</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a040dc9c0273fc4e29dd872c1928f97b6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>ae71d4892ea462f1f1013e7505de1b6bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateVertexBuffer</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a52563201d1e14cd004f0a33696f61769</anchor>
      <arglist>(const stTexVertex *const pVertices)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateIndexBuffer</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>ab7679ec7393d7250bd3f506a296634c0</anchor>
      <arglist>(const unsigned long *const pIndices)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11Buffer *</type>
      <name>m_pVertexBuffer</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a14b9601bb6fd997a09213edef503b315</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11Buffer *</type>
      <name>m_pIndexBuffer</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a6867ecf0b38aaf06e55e9b73f5c0e9bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT</type>
      <name>m_iVertexCount</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a3739e88adce1438f9fcb7037723f8dc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT</type>
      <name>m_iIndexCount</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a7ae116711751e2374705614924d91de5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT</type>
      <name>m_iVertexSize</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a887775421dc4f151db74f0ebf6ffd466</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; cTextureShader &gt;</type>
      <name>m_pShader</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>ad1e17c41efbb0890ec81c59cdaf8b560</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; stObjectSubset &gt;</type>
      <name>m_vSubsets</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a349bae0991305c24035c91625fb2d41c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DXMATRIX</type>
      <name>m_matWorld</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>aad6232336004df2079d0e5997cb6c1e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>IBoundingBox *</type>
      <name>m_pBoundingBox</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a3adfd6292d47cb7e1d3e9952c04b1345</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cVector3</type>
      <name>m_vBoundingSphereCentre</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>a6120be9e969cabf926c6212bb5a39675</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fBoundingSphereRadius</name>
      <anchorfile>class_graphics_1_1c_model.html</anchorfile>
      <anchor>af60d56a67666cd829fdef848500506d5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Graphics::cModel::stObjectSubset</name>
    <filename>struct_graphics_1_1c_model_1_1st_object_subset.html</filename>
    <member kind="variable">
      <type>UINT</type>
      <name>m_iIndexCountInSubset</name>
      <anchorfile>struct_graphics_1_1c_model_1_1st_object_subset.html</anchorfile>
      <anchor>a8c83ae91d46a153c304d2cc6a16d7b18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UINT</type>
      <name>m_iStartIndexNo</name>
      <anchorfile>struct_graphics_1_1c_model_1_1st_object_subset.html</anchorfile>
      <anchor>aaf8aea0cea9fef4e975ba64488362a8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Base::cColor</type>
      <name>m_diffuseColor</name>
      <anchorfile>struct_graphics_1_1c_model_1_1st_object_subset.html</anchorfile>
      <anchor>aa559033b81b4fbed5fc0f0afb6a474bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>shared_ptr&lt; Graphics::ITexture &gt;</type>
      <name>m_pTexture</name>
      <anchorfile>struct_graphics_1_1c_model_1_1st_object_subset.html</anchorfile>
      <anchor>a9a67f84b42fc624bc76d7e3a3717b2c7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cScrollBarControl</name>
    <filename>class_graphics_1_1c_scroll_bar_control.html</filename>
    <base>Graphics::cBaseControl</base>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VSetThumbPosition</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a4d0cea896c58f630fd69bc29ef4aa88e</anchor>
      <arglist>(const int iNewPosition)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_iMinPos</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>ac4dd3c741eeab2b4442930d36d6fb17f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_iMaxPos</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a64cbfcd14a2b9df0f11f6762fe96c3d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_iThumbPos</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>acdd054b6bd9326379a91df9d810c3d46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_iNoOfIncrements</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a9d7f9e6f3581d171b0bdf46fdd1f734f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_bDragMode</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a2c05a0e43b61856caff71252b066f445</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>IBaseControl *</type>
      <name>m_pBtnThumb</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>ac682ddbc374912eba0c0eed0b31c7d57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>IBaseControl *</type>
      <name>m_pBtnDecrementArrow</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>aaa7a6f3a831d11c866cb8d1527855bcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>IBaseControl *</type>
      <name>m_pBtnIncrementArrow</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a30a21463a2b2be0f61a95c8abe2854e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>UIEventCallBackFn</type>
      <name>m_callbackIncrementArrowPressed</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a21612b6db7feca1cd46fd6b7d458045b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>UIEventCallBackFn</type>
      <name>m_callbackDecrementArrowPressed</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a69ea97cdd57433ac36eabe730b3a4ac0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>UIEventCallBackFn</type>
      <name>m_callbackThumbPressed</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>adb0d823bdfb61892f332143b25d9ca38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>UIEventCallBackFn</type>
      <name>m_callbackThumbReleased</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a775c840a6f2b3961a41800eaeb9dcb5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnLeftMouseButtonUp</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a58d6240a0628bda12730c84d5dc02c8f</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnLeftMouseButtonDown</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a3a9cd338332c3b6508b5395ad73c5c83</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a15302faa07ea4d0ba7fc7aa3cb87f7f8</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a6000d1e9eb9e299f839471b13306359d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>IncrementArrowPressed</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a57fffea6c41bcdcbbad317e5dc493d2e</anchor>
      <arglist>(const Graphics::stUIEventCallbackParam &amp;params)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>DecrementArrowPressed</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a71b2eb6d5696680d788062923a98dd59</anchor>
      <arglist>(const Graphics::stUIEventCallbackParam &amp;params)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ThumbPressed</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>a7a93b4aafaa242b4c4e266387cd4cba3</anchor>
      <arglist>(const Graphics::stUIEventCallbackParam &amp;params)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ThumbReleased</name>
      <anchorfile>class_graphics_1_1c_scroll_bar_control.html</anchorfile>
      <anchor>ab5efaccad4207691ac6cfbacc89d860c</anchor>
      <arglist>(const Graphics::stUIEventCallbackParam &amp;params)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cSentence</name>
    <filename>class_graphics_1_1c_sentence.html</filename>
    <base>Graphics::ISentence</base>
    <base protection="private">Base::cNonCopyable</base>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>ae68d8d03ea040daad7ea368054e2eb46</anchor>
      <arglist>(const Base::cString &amp;strFont, const Base::cString &amp;strText, const Base::cColor &amp;textColor)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a275dbcd805b90c6583b4077121d9ec24</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>ae4a23de3842580c0d2ae7d7a4cfea5b8</anchor>
      <arglist>(const Base::cVector2 &amp;vPosition)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VGetText</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a605335c1e6c34274204d498cc624ef6e</anchor>
      <arglist>(Base::cString &amp;strText) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetText</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>adc28cbb35c945d7b360f9ea0d9bb619f</anchor>
      <arglist>(const Base::cString &amp;strText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetTextColor</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a41f414e577e5457e4292689bf3207c54</anchor>
      <arglist>(const Base::cColor &amp;colorText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>VGetWidth</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a8630e1e375ebe36bceb1e4e3eec778d5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>VGetWidth</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>ac6927902d3bf8bc862f0f01df72b83f4</anchor>
      <arglist>(const Base::cString &amp;strText) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>VGetHeight</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>ae5ac1156514f5022b029225151d05838</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetHeight</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>abf4a7a3992ff93ec510b256b5ebcbf99</anchor>
      <arglist>(const float fTextHeight)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateVertexBuffer</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a94e40427b2fb7036db6bf1ef18a940f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CreateIndexBuffer</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a0446c5fbcc25d2fc7b0a89b5418a5810</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>ReInitializeVertexBuffer</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>abfd66e36e762ce8ea1c3eb45d36ca29d</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InitializesVertexData</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>aa31d125281035589d11cf506cdfc792c</anchor>
      <arglist>(stTexVertex *const pVertices, const int iLineLength, const int iStartPos, const Base::cVector2 &amp;vPos, float &amp;fWidth)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Cleanup</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>af2e93b58d424fcda52e718363162f8e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11Buffer *</type>
      <name>m_pVertexBuffer</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>acea5d3992a2e9c07295ec36333fca1d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11Buffer *</type>
      <name>m_pIndexBuffer</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a188929a22eb5f92b5a74a781a65ebb53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cString</type>
      <name>m_strText</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a8a8d993e9fca4f3a537488b4b153d630</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; IMyFont &gt;</type>
      <name>m_pFont</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>adef90e0ee75c380a87d914474708ca16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cColor</type>
      <name>m_TextColor</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>ac9a2b8e4a6ad830182f85f4d0f7ee2f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iVertexCount</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a13e349f5b23ef771339385efcc10e6fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iIndexCount</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a624407606da4dea39e045f1569fb7277</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Base::cVector2</type>
      <name>m_vPosition</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a1e6e96fb52e30fcc25f7a59530afb627</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bIsDirty</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a11f7eab5bcf164a7e2472a58ef593142</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fWidth</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>a8ef726875760f6b2356907f207909dc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fHeight</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>af18224ab3c4260d3ba0f8abb9934a9a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fScale</name>
      <anchorfile>class_graphics_1_1c_sentence.html</anchorfile>
      <anchor>aa48c41f0495bf7ec7dfc1e4aa57ccf93</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IShader</name>
    <filename>class_graphics_1_1_i_shader.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1_i_shader.html</anchorfile>
      <anchor>aa9f28a2530d15fc85a214aa826f31e3e</anchor>
      <arglist>(const Base::cString &amp;strShaderName)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1_i_shader.html</anchorfile>
      <anchor>a3a961596eb801393ffbfec082727c91b</anchor>
      <arglist>(const D3DXMATRIX &amp;inMatWorld, const D3DXMATRIX &amp;inMatView, const D3DXMATRIX &amp;inMatProjection)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VSetTexture</name>
      <anchorfile>class_graphics_1_1_i_shader.html</anchorfile>
      <anchor>afe9ac5eebdd880f2cca2fd0e01454226</anchor>
      <arglist>(shared_ptr&lt; ITexture &gt; pTexture)=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IShader *const</type>
      <name>CreateColorShader</name>
      <anchorfile>class_graphics_1_1_i_shader.html</anchorfile>
      <anchor>a46bbe663cf9478739e12f4157d4f77d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IShader *const</type>
      <name>CreateTextureShader</name>
      <anchorfile>class_graphics_1_1_i_shader.html</anchorfile>
      <anchor>aba45bfb7ca4514c0ba1b2f02fb16053c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IShader *const</type>
      <name>CreateFontShader</name>
      <anchorfile>class_graphics_1_1_i_shader.html</anchorfile>
      <anchor>a7af41f6a8d04e49d6797b301abd25547</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cShaderManager</name>
    <filename>class_graphics_1_1c_shader_manager.html</filename>
    <base>Graphics::IShaderManager</base>
    <member kind="function" static="yes">
      <type>static IShaderManager *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_shader_manager.html</anchorfile>
      <anchor>a5694dbc18de3d91310321ff980f87588</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static IShaderManager *</type>
      <name>s_pShadermanager</name>
      <anchorfile>class_graphics_1_1c_shader_manager.html</anchorfile>
      <anchor>a8c7dfdb40d8e197b850a23e81d89ffe6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; unsigned long, shared_ptr&lt; IShader &gt; &gt;</type>
      <name>ShaderMap</name>
      <anchorfile>class_graphics_1_1c_shader_manager.html</anchorfile>
      <anchor>a5f444c413b20cd133ace970465530347</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VGetShader</name>
      <anchorfile>class_graphics_1_1c_shader_manager.html</anchorfile>
      <anchor>abd3c3eb5c21523e5b25b551c0f7e9237</anchor>
      <arglist>(shared_ptr&lt; IShader &gt; &amp;pShader, const Base::cString &amp;strShaderName)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>shared_ptr&lt; IShader &gt;</type>
      <name>Find</name>
      <anchorfile>class_graphics_1_1c_shader_manager.html</anchorfile>
      <anchor>ad4eac414e5bb27e9310426525d7f7d86</anchor>
      <arglist>(const unsigned long ulShaderHash)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ShaderMap</type>
      <name>m_pShaders</name>
      <anchorfile>class_graphics_1_1c_shader_manager.html</anchorfile>
      <anchor>ad79f35703fa1062a32b39d2a3d446c53</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::IShaderManager</name>
    <filename>class_graphics_1_1_i_shader_manager.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>VGetShader</name>
      <anchorfile>class_graphics_1_1_i_shader_manager.html</anchorfile>
      <anchor>a4e42d9a1a5130c1250c2b8b3700f2cc7</anchor>
      <arglist>(shared_ptr&lt; IShader &gt; &amp;pShader, const Base::cString &amp;strShaderName)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cSprite</name>
    <filename>class_graphics_1_1c_sprite.html</filename>
    <base>Graphics::ISprite</base>
    <base>Base::cNonCopyable</base>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a43dc2734ad16a7a8a0b0b8a741fc7c7a</anchor>
      <arglist>(shared_ptr&lt; ITexture &gt; const pTexture)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a983614d2ec0ee00d27a1d784dac655dc</anchor>
      <arglist>(const Base::cString &amp;strTextureFilename)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>ac7f054a3b9d48f6e17662e3fc27923c1</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>ac1ebf198f0247b05903f6758f73b8f86</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>VSetPosition</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a10d7230f2018738dadc0fe195130353e</anchor>
      <arglist>(const Base::cVector2 &amp;vPosition)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>VSetSize</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>ac5c1814d5570cf30ffb89813a038947b</anchor>
      <arglist>(const Base::cVector2 &amp;vSize)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Base::cVector2</type>
      <name>VGetSize</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>aebbbf56a3f544b88587ff687e50ec696</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateVertexBuffer</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a0a24d76c1a9a425ec290d4d0c1cf5ace</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>CreateIndexBuffer</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>ac44c4e8edfe907e0e4862d1fef5ce03a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ID3D11Buffer *</type>
      <name>m_pVertexBuffer</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a0cb5401ce86f56e44adeed75deb3c3b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ID3D11Buffer *</type>
      <name>m_pIndexBuffer</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a237ea7b8775f59c7ad50762912e0e5e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>shared_ptr&lt; IShader &gt;</type>
      <name>m_pShader</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>ab859f0aac2d58222c83b9ae1aacbe6b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>shared_ptr&lt; Graphics::ITexture &gt;</type>
      <name>m_pTexture</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>af2672765f5cc93010c592b4cf50db869</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Base::cVector2</type>
      <name>m_vSize</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>ab8f72a170a6015cd1d707083461c1529</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Base::cVector2</type>
      <name>m_vPosition</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a83987f3239a1a620bdd6e06cc1c818d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_bIsDirty</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>adfbec5cd9b5ef3ab5bc1828213448ade</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_iIndexCount</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>aa9fbbec8651235b3d1708236c0e4a8f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_iVertexCount</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>aa52cfc1cdbd71d20925f7df5a92ff175</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetTexture</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a175e00d43e6c67b1a128dc7a060ddc9c</anchor>
      <arglist>(shared_ptr&lt; ITexture &gt; const pTexture)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>InitializeShader</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a640992307812f4e33c3de13cc9f9c74c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>RecalculateVertexData</name>
      <anchorfile>class_graphics_1_1c_sprite.html</anchorfile>
      <anchor>a39e01173b9b53f20ec63c30e0409cd53</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cTextBoxControl</name>
    <filename>class_graphics_1_1c_text_box_control.html</filename>
    <base>Graphics::cBaseControl</base>
    <member kind="function">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a2401bad815210e44c16d40896627ac07</anchor>
      <arglist>(const cTextBoxControlDef &amp;def)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VRender</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>ae58fdd8144781e7f7e559f2472e87d8d</anchor>
      <arglist>(const ICamera *const pCamera)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnKeyDown</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>aaa3837e4407029dfc43a55a76ff1bf2e</anchor>
      <arglist>(const unsigned int iCharID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnCharPress</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a5fb902c84f40bc1d4166157aa3d911ad</anchor>
      <arglist>(const unsigned int iCharID)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetText</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a137666ffade47277e4f62763580017b5</anchor>
      <arglist>(const Base::cString &amp;strText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a2e7f82e8be4e74e9ec53c99ba6ccad8c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VOnFocusChanged</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a56e6d938cf17f81a264e3e0438cf8fb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>ad0ca60f8f2fb5fdeac2a8b0450b977dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>InsertText</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a7d9757420dffc50d96132392dcab80d1</anchor>
      <arglist>(const Base::cString &amp;strText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RemoveText</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a7eb691d065900da7e507fa9d6e1986ec</anchor>
      <arglist>(const unsigned int uiQuantity)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>GetStringWidth</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a4cb9c24dee5c533fbb15980ccd274920</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>GetStringWidth</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>af619455c52d5c446bc3d81a1e0a1cfe4</anchor>
      <arglist>(const Base::cString &amp;strText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetText</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a67d550ed9ef59e7f7c01357232e1f2c9</anchor>
      <arglist>(const Base::cString &amp;strText)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>SetCaratPosition</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a61bee3f3a35d00db763fc6267650df9e</anchor>
      <arglist>(const unsigned int iPos)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetCaratAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>ab63e4f823ca8492055e46fd09faa7b88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ISentence *</type>
      <name>m_pSentence</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a77bfe12289055314b04f28731f59dcab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>shared_ptr&lt; ISprite &gt;</type>
      <name>m_pCaretSprite</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a0004e49537730db769fe12377d51978c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fCaretPosInTextBox</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a3d8b4b41a34913a9b17e6a3df9aa3cc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fLastCaretUpdateTime</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a99c2ef5a9b87b2b5ba6960d9859f1c2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned int</type>
      <name>m_iCaretPosInText</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a1ade58cf397c6838c9e3fa1df73d914e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bTextBoxFull</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a2810cfed9401f23265fd1d2bf2109656</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fCaretUpdateTime</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>ac2f5a61c6e5704587b23716a27189217</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Utilities::ITimer *</type>
      <name>m_pTimer</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>ac77e9b422506071c19b615904cd40e17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bIsCaretVisible</name>
      <anchorfile>class_graphics_1_1c_text_box_control.html</anchorfile>
      <anchor>a1b47c9e671da092c6381b6a06d94e9cd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cTexture</name>
    <filename>class_graphics_1_1c_texture.html</filename>
    <base>Graphics::ITexture</base>
    <base>Base::cNonCopyable</base>
    <member kind="function">
      <type>bool</type>
      <name>Initialize</name>
      <anchorfile>class_graphics_1_1c_texture.html</anchorfile>
      <anchor>ae8bb468bf791854f795eeea9320b793f</anchor>
      <arglist>(const Base::cString &amp;strTexturePath)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ID3D11ShaderResourceView *</type>
      <name>VGetTexture</name>
      <anchorfile>class_graphics_1_1c_texture.html</anchorfile>
      <anchor>ab2fc7df636884a83f53b7c570aa5d31d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Cleanup</name>
      <anchorfile>class_graphics_1_1c_texture.html</anchorfile>
      <anchor>aac8b28797bab937f6df28476e50281c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11ShaderResourceView *</type>
      <name>m_pTexture</name>
      <anchorfile>class_graphics_1_1c_texture.html</anchorfile>
      <anchor>a190142ba0c614602616dc042cc0ff123</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::ITexture</name>
    <filename>class_graphics_1_1_i_texture.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual ID3D11ShaderResourceView *</type>
      <name>VGetTexture</name>
      <anchorfile>class_graphics_1_1_i_texture.html</anchorfile>
      <anchor>aa5b5ffb949e1a7b8a8619b80dbc63449</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static shared_ptr&lt; ITexture &gt;</type>
      <name>CreateTexture</name>
      <anchorfile>class_graphics_1_1_i_texture.html</anchorfile>
      <anchor>a406870d36250a508f39b59002976d5f1</anchor>
      <arglist>(const Base::cString &amp;strTexturePath)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cTextureManager</name>
    <filename>class_graphics_1_1c_texture_manager.html</filename>
    <base>Graphics::ITextureManager</base>
    <member kind="function" static="yes">
      <type>static ITextureManager *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_texture_manager.html</anchorfile>
      <anchor>a47a5e093f28180612b7e871d6b2c69e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static ITextureManager *</type>
      <name>s_pTexturemanager</name>
      <anchorfile>class_graphics_1_1c_texture_manager.html</anchorfile>
      <anchor>a210155f31ed11a8285d5f8d65065ff42</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; unsigned long, shared_ptr&lt; ITexture &gt; &gt;</type>
      <name>TextureMap</name>
      <anchorfile>class_graphics_1_1c_texture_manager.html</anchorfile>
      <anchor>a6bbf75dd7eb12de5c51152fbb3223eb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>shared_ptr&lt; ITexture &gt;</type>
      <name>VGetTexture</name>
      <anchorfile>class_graphics_1_1c_texture_manager.html</anchorfile>
      <anchor>a9d39f3ba844d1412f4d78183837a1110</anchor>
      <arglist>(const Base::cString &amp;strTexturePath)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>shared_ptr&lt; ITexture &gt;</type>
      <name>Find</name>
      <anchorfile>class_graphics_1_1c_texture_manager.html</anchorfile>
      <anchor>a5d29feda065a2c9abaebc5464e93a51f</anchor>
      <arglist>(const unsigned long ulTextureHash)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TextureMap</type>
      <name>m_pTextures</name>
      <anchorfile>class_graphics_1_1c_texture_manager.html</anchorfile>
      <anchor>a5f55a6cb5a7a7a6d30512fb197bada69</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::ITextureManager</name>
    <filename>class_graphics_1_1_i_texture_manager.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual shared_ptr&lt; ITexture &gt;</type>
      <name>VGetTexture</name>
      <anchorfile>class_graphics_1_1_i_texture_manager.html</anchorfile>
      <anchor>a742ee9fdac4ee46352b77968b199fe56</anchor>
      <arglist>(const Base::cString &amp;strTexturePath)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cTextureShader</name>
    <filename>class_graphics_1_1c_texture_shader.html</filename>
    <base>Graphics::cBaseShader</base>
    <member kind="function">
      <type>void</type>
      <name>SetDiffuseColor</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>af53e7658a785578b2cea745b2d406b5b</anchor>
      <arglist>(const Base::cColor colorDiffuse)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>VInitialize</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>ae4d6bf8fbf8366b2c64c9e6fb2d25132</anchor>
      <arglist>(const Base::cString &amp;strShaderName)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>VCreateLayout</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>ab96bc4a9459d2763ab2a642be979d3b9</anchor>
      <arglist>(shared_ptr&lt; Utilities::IResHandle const  &gt; shaderHandle)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VSetShaderParameters</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>a6d9d4759c3dd821c92cb901ccc4e3fb0</anchor>
      <arglist>(const D3DXMATRIX &amp;inMatWorld, const D3DXMATRIX &amp;inMatView, const D3DXMATRIX &amp;inMatProjection)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VRenderShader</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>abc43800ed61f3a54c09b051495ecea77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>VCleanup</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>a939044041ed68bc590856847b2fdc025</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreatePixelBuffer</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>adf587ff8050830ec5ddaeba8118c2913</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateSampleState</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>a65e4ea431c49eac0d982c392624378c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ID3D11Buffer *</type>
      <name>m_pPixelBuffer</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>a91e6b4071703987ae6bb76f41088345c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>D3DXVECTOR4</type>
      <name>m_DiffuseColor</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>ab69af636774e9fd21c1f98310acd6108</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ID3D11SamplerState *</type>
      <name>m_pSampleState</name>
      <anchorfile>class_graphics_1_1c_texture_shader.html</anchorfile>
      <anchor>a1e5c87781aa333b916c16ffe3a19b7fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cVScrollBar</name>
    <filename>class_graphics_1_1c_v_scroll_bar.html</filename>
    <base>Graphics::cScrollBarControl</base>
    <member kind="function" static="yes">
      <type>static cVScrollBar *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_v_scroll_bar.html</anchorfile>
      <anchor>a1279e5749a5f846d6e4409eb53df62ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnMouseMove</name>
      <anchorfile>class_graphics_1_1c_v_scroll_bar.html</anchorfile>
      <anchor>a85d6af0c4279e6f9e07af06803a6254b</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_v_scroll_bar.html</anchorfile>
      <anchor>a18dbcab670268cb09783fdbd763281f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetSize</name>
      <anchorfile>class_graphics_1_1c_v_scroll_bar.html</anchorfile>
      <anchor>a69617297616ad63d1706e2252af3e872</anchor>
      <arglist>(const Base::cVector2 &amp;vSize)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetThumbPosition</name>
      <anchorfile>class_graphics_1_1c_v_scroll_bar.html</anchorfile>
      <anchor>a272ab646e23905d4ce566973a66a9400</anchor>
      <arglist>(const int iNewPosition)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>AutoSizeThumb</name>
      <anchorfile>class_graphics_1_1c_v_scroll_bar.html</anchorfile>
      <anchor>a47b9ad3cd9e593c199bb272073058739</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cWindowControl</name>
    <filename>class_graphics_1_1c_window_control.html</filename>
    <base>Graphics::cBaseControl</base>
    <member kind="function">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>class_graphics_1_1c_window_control.html</anchorfile>
      <anchor>a90e739ece86ce78726aed09b36720da0</anchor>
      <arglist>(const cWindowControlDef &amp;def)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnLeftMouseButtonUp</name>
      <anchorfile>class_graphics_1_1c_window_control.html</anchorfile>
      <anchor>a22113bebe1a6de5c2bf814b16b2b6089</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnLeftMouseButtonDown</name>
      <anchorfile>class_graphics_1_1c_window_control.html</anchorfile>
      <anchor>a95b37b496917f06312c640cbe236253b</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VOnMouseMove</name>
      <anchorfile>class_graphics_1_1c_window_control.html</anchorfile>
      <anchor>a437c6ee14caa1521689205a92236a4e6</anchor>
      <arglist>(const int X, const int Y)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VSetAbsolutePosition</name>
      <anchorfile>class_graphics_1_1c_window_control.html</anchorfile>
      <anchor>ac5f87198bc38c92113407347e8ed68dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>cWindowControlDef::WINDOWTYPE</type>
      <name>m_eWindowType</name>
      <anchorfile>class_graphics_1_1c_window_control.html</anchorfile>
      <anchor>a2922cc249677420115219c33533d4fa4</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
