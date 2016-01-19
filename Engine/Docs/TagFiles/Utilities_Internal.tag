<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>Utilities::IResourceManager</name>
    <filename>class_utilities_1_1_i_resource_manager.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VInitialize</name>
      <anchorfile>class_utilities_1_1_i_resource_manager.html</anchorfile>
      <anchor>aa1840c989510f70c127b0ccba492e7b0</anchor>
      <arglist>(const Base::cString strPath)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Utilities::IResCache *</type>
      <name>VGetResourceCache</name>
      <anchorfile>class_utilities_1_1_i_resource_manager.html</anchorfile>
      <anchor>a4498cf0556cc9e700406df79f2ca3a61</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static UTILITIES_API IResourceManager *</type>
      <name>GetInstance</name>
      <anchorfile>class_utilities_1_1_i_resource_manager.html</anchorfile>
      <anchor>ae82c3b538a24c623b4382d3f1ebd63bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static UTILITIES_API void</type>
      <name>Destroy</name>
      <anchorfile>class_utilities_1_1_i_resource_manager.html</anchorfile>
      <anchor>a7683a0b6aba149c528627d23f07bd3c0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Utilities::ITimer</name>
    <filename>class_utilities_1_1_i_timer.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API void</type>
      <name>VStartTimer</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>a64db005d9ea7a0344b21c6a2c28da2f9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API void</type>
      <name>VStopTimer</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>ab03bd586cb22bdd2c2199d01b68848c6</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API void</type>
      <name>VOnUpdate</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>a1a3915891b0432c5c78da24dace6fd67</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API bool</type>
      <name>VIsStopped</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>a9a7dbbd218141d3fe48a9317e78c5598</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API float</type>
      <name>VGetFPS</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>a903acb1ed6feefce8e29a115ff303024</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API float</type>
      <name>VGetRunningTime</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>a0788bee07fd5b6a6992ca85d323ead85</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API TICK</type>
      <name>VGetRunningTicks</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>aa08f90081abebba3ad2bf437a69b8652</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual UTILITIES_API float</type>
      <name>VGetDeltaTime</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>afb4bb03bfbbce443176d5ae605e700f5</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static UTILITIES_API ITimer *</type>
      <name>CreateTimer</name>
      <anchorfile>class_utilities_1_1_i_timer.html</anchorfile>
      <anchor>a8f8818cf0672d7cd380ccd62274b33a0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Utilities::cResourceManager</name>
    <filename>class_utilities_1_1c_resource_manager.html</filename>
    <base>Utilities::IResourceManager</base>
    <base>Base::cNonCopyable</base>
    <member kind="function" static="yes">
      <type>static IResourceManager *</type>
      <name>Create</name>
      <anchorfile>class_utilities_1_1c_resource_manager.html</anchorfile>
      <anchor>ad977aa284d8c6a61fff2841628536522</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static IResourceManager *</type>
      <name>s_pResourceManager</name>
      <anchorfile>class_utilities_1_1c_resource_manager.html</anchorfile>
      <anchor>a25232b731e9f83c6e690a3dec2fd2c87</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VInitialize</name>
      <anchorfile>class_utilities_1_1c_resource_manager.html</anchorfile>
      <anchor>ae83a5c20622fadd71bf9e128159bc7b5</anchor>
      <arglist>(const Base::cString strPath)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Utilities::IResCache *</type>
      <name>VGetResourceCache</name>
      <anchorfile>class_utilities_1_1c_resource_manager.html</anchorfile>
      <anchor>ae3850659c131692da2b6688f04d1fb48</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Utilities::IResCache *</type>
      <name>m_pResourceCache</name>
      <anchorfile>class_utilities_1_1c_resource_manager.html</anchorfile>
      <anchor>a64803216ef1627f11c57dc797a8c32d8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Utilities::cTimer</name>
    <filename>class_utilities_1_1c_timer.html</filename>
    <base>Utilities::ITimer</base>
    <base>Base::cNonCopyable</base>
    <member kind="function" static="yes">
      <type>static cTimer *</type>
      <name>Create</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a1c879a547718f11290412338a101b8d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VStartTimer</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a86eb9bab2c3c681f74ffecee65a8dc80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VStopTimer</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>ab358f0173dc8b91f6b7ec62df03b27c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VOnUpdate</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a1f697703799271667ccd227b5d2daa28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>VIsStopped</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a933f26b123462ce78ddac2f3d8789651</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>VGetFPS</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>aafd3b1719939841cb0d1ac1a57ab3316</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>VGetRunningTime</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a0ab040dee86474f1a936c399fb410e69</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>VGetDeltaTime</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a0cfa007bbdbdbbef6ecf3f2b438b3054</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>TICK</type>
      <name>VGetRunningTicks</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a00356aeb7b8ca8a0fe82faf8a7009a0a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>INT64</type>
      <name>m_iTicksPerSecond</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a4f73d1285725ad5220b57260840d6d92</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>INT64</type>
      <name>m_iCurrentTime</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a8c06c80066a4255ee88c44e4bef1d91a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>INT64</type>
      <name>m_iLastUpdateTime</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>af7cd3a3f8b3dc8eb6da16a985b8439ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>INT64</type>
      <name>m_iLastFPSUpdateTime</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a8ed3cac3189a3b0cfe31041d3ca04c47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>INT64</type>
      <name>m_iFPSUpdateInterval</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a6c91bf0678a9613888df15d0e0a7d30d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT</type>
      <name>m_iNumFrames</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>afb2efba36211ba36f330aa82f95e2d7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UINT</type>
      <name>m_iTotalsFrames</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>ad73cb61b09f349fc0a4b1700f405b428</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fRunningTime</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>abcc47da4ec0962753936756d3bee97e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fDeltaTime</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>ac8358aab78960e6fbdfa16b968439b7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_fFPS</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>a3a75fb13c2ad10b253690e4085656ecd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bTimerStopped</name>
      <anchorfile>class_utilities_1_1c_timer.html</anchorfile>
      <anchor>aef7ad5595fa1f94920dc056043b7c3f4</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
