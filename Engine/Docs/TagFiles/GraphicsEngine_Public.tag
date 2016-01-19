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
      <anchor>a6beb33063de0ea7798318c68f9823dda</anchor>
      <arglist>(const cWindowControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateLabelControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a84a4904f444d897f883418398c891e06</anchor>
      <arglist>(const cLabelControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateButtonControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>abe3cd627613c880ac0d18769b7c1a8ae</anchor>
      <arglist>(const cButtonControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateCheckBoxControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a1ea70f1c1b452bfe78d4607ccdf3ded4</anchor>
      <arglist>(const cCheckBoxControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateTextBoxControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>a0a1a73bba537e18c2efecab74f087fd1</anchor>
      <arglist>(const cTextBoxControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateVScrollBarControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>ad60aab5fb0b335fa38bc731b951652e3</anchor>
      <arglist>(const cScrollBarControlDef &amp;def)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IBaseControl *</type>
      <name>CreateHScrollBarControl</name>
      <anchorfile>class_graphics_1_1_i_base_control.html</anchorfile>
      <anchor>aeb9cfdc3c17e88283ab909976939009b</anchor>
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
      <anchor>aee5382f674ad5c94bebce117f5925d0b</anchor>
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
      <anchor>a8c2e68de7f25f335e91f195affd3fcf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API void</type>
      <name>Destroy</name>
      <anchorfile>class_graphics_1_1_i_graphics_class.html</anchorfile>
      <anchor>a3f52e4c0dd20eade15884e8e84b40eb0</anchor>
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
      <anchor>acb74ccc7d895e23dcf06d6d33819baa4</anchor>
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
      <anchor>adf5aed04a2ce9a844a7eec2f224a11fb</anchor>
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
      <anchor>a47dca35a639358c3a619d3a9fa34da36</anchor>
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
      <anchor>a888b338d62cfe17e36d1522f049e6da1</anchor>
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
</tagfile>
