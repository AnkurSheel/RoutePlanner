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
      <anchor>a985a7e64f7f08bd288fe03e50da81f81</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static UTILITIES_API void</type>
      <name>Destroy</name>
      <anchorfile>class_utilities_1_1_i_resource_manager.html</anchorfile>
      <anchor>a21ba7cb6cd2250c52f9d18e703b50b95</anchor>
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
      <anchor>acf7f6af4d9ca4eb755a95d333e7be694</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
</tagfile>
