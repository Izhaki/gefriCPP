##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Win32_Debug
ProjectName            :=gefri
ConfigurationName      :=Win32_Debug
IntermediateDirectory  :=./build/Win32-Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "Z:\gefri\build"
ProjectPath            := "Z:\gefri\build\gefri"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Administrator
Date                   :=07/01/11
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=./../../lib/lib$(ProjectName)_msw32d.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Z:\gefri\build\gefri\gefri.txt"
MakeDirCommand         :=makedir
CmpOptions             := -g $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
C_CmpOptions           := -g $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
LinkOptions            :=  $(shell wx-config --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)../../src 
RcIncludePath          :=
Libs                   :=
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
WXWIN:=C:\wxWidgets-2.8.12
PATH:=$(WXWIN)\lib\gcc_lib;$(PATH)
WXCFG:=gcc_lib\mswu
Objects=$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) $(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix) $(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) $(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) \
	$(IntermediateDirectory)/lightweights_gxScaler$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxStructuralViewElement$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

./build/Win32-Debug:
	@$(MakeDirCommand) "./build/Win32-Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix): ../../src/adapters/wx/gxLightweightControl.cpp $(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/adapters/wx/gxLightweightControl.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix): ../../src/adapters/wx/gxLightweightControl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) -MF$(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix) -MM "Z:/gefri/src/adapters/wx/gxLightweightControl.cpp"

$(IntermediateDirectory)/wx_gxLightweightControl$(PreprocessSuffix): ../../src/adapters/wx/gxLightweightControl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wx_gxLightweightControl$(PreprocessSuffix) "Z:/gefri/src/adapters/wx/gxLightweightControl.cpp"

$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix): ../../src/core/gxComposite.cpp $(IntermediateDirectory)/core_gxComposite$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/core/gxComposite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_gxComposite$(DependSuffix): ../../src/core/gxComposite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) -MF$(IntermediateDirectory)/core_gxComposite$(DependSuffix) -MM "Z:/gefri/src/core/gxComposite.cpp"

$(IntermediateDirectory)/core_gxComposite$(PreprocessSuffix): ../../src/core/gxComposite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_gxComposite$(PreprocessSuffix) "Z:/gefri/src/core/gxComposite.cpp"

$(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix): ../../src/lightweights/gxDcPainter.cpp $(IntermediateDirectory)/lightweights_gxDcPainter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxDcPainter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxDcPainter$(DependSuffix): ../../src/lightweights/gxDcPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxDcPainter$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxDcPainter.cpp"

$(IntermediateDirectory)/lightweights_gxDcPainter$(PreprocessSuffix): ../../src/lightweights/gxDcPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxDcPainter$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxDcPainter.cpp"

$(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix): ../../src/lightweights/gxLightweightSystem.cpp $(IntermediateDirectory)/lightweights_gxLightweightSystem$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxLightweightSystem.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxLightweightSystem$(DependSuffix): ../../src/lightweights/gxLightweightSystem.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxLightweightSystem$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxLightweightSystem.cpp"

$(IntermediateDirectory)/lightweights_gxLightweightSystem$(PreprocessSuffix): ../../src/lightweights/gxLightweightSystem.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxLightweightSystem$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxLightweightSystem.cpp"

$(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix): ../../src/lightweights/gxPainter.cpp $(IntermediateDirectory)/lightweights_gxPainter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxPainter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxPainter$(DependSuffix): ../../src/lightweights/gxPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxPainter$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxPainter.cpp"

$(IntermediateDirectory)/lightweights_gxPainter$(PreprocessSuffix): ../../src/lightweights/gxPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxPainter$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxPainter.cpp"

$(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix): ../../src/lightweights/gxRootViewElement.cpp $(IntermediateDirectory)/lightweights_gxRootViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxRootViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxRootViewElement$(DependSuffix): ../../src/lightweights/gxRootViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxRootViewElement$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxRootViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxRootViewElement$(PreprocessSuffix): ../../src/lightweights/gxRootViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxRootViewElement$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxRootViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix): ../../src/lightweights/gxViewElement.cpp $(IntermediateDirectory)/lightweights_gxViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxViewElement$(DependSuffix): ../../src/lightweights/gxViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxViewElement$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxViewElement$(PreprocessSuffix): ../../src/lightweights/gxViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxViewElement$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix): ../../src/lightweights/gxVisualViewElement.cpp $(IntermediateDirectory)/lightweights_gxVisualViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxVisualViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxVisualViewElement$(DependSuffix): ../../src/lightweights/gxVisualViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxVisualViewElement$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxVisualViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxVisualViewElement$(PreprocessSuffix): ../../src/lightweights/gxVisualViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxVisualViewElement$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxVisualViewElement.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix): ../../src/lightweights/shapes/gxRectangle.cpp $(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/shapes/gxRectangle.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix): ../../src/lightweights/shapes/gxRectangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix) -MM "Z:/gefri/src/lightweights/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix): ../../src/lightweights/shapes/gxRectangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix) "Z:/gefri/src/lightweights/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix): ../../src/lightweights/shapes/gxShape.cpp $(IntermediateDirectory)/shapes_gxShape$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/shapes/gxShape.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxShape$(DependSuffix): ../../src/lightweights/shapes/gxShape.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxShape$(DependSuffix) -MM "Z:/gefri/src/lightweights/shapes/gxShape.cpp"

$(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix): ../../src/lightweights/shapes/gxShape.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix) "Z:/gefri/src/lightweights/shapes/gxShape.cpp"

$(IntermediateDirectory)/lightweights_gxScaler$(ObjectSuffix): ../../src/lightweights/gxScaler.cpp $(IntermediateDirectory)/lightweights_gxScaler$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxScaler.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxScaler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxScaler$(DependSuffix): ../../src/lightweights/gxScaler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxScaler$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxScaler$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxScaler.cpp"

$(IntermediateDirectory)/lightweights_gxScaler$(PreprocessSuffix): ../../src/lightweights/gxScaler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxScaler$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxScaler.cpp"

$(IntermediateDirectory)/lightweights_gxStructuralViewElement$(ObjectSuffix): ../../src/lightweights/gxStructuralViewElement.cpp $(IntermediateDirectory)/lightweights_gxStructuralViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/src/lightweights/gxStructuralViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxStructuralViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxStructuralViewElement$(DependSuffix): ../../src/lightweights/gxStructuralViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxStructuralViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxStructuralViewElement$(DependSuffix) -MM "Z:/gefri/src/lightweights/gxStructuralViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxStructuralViewElement$(PreprocessSuffix): ../../src/lightweights/gxStructuralViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxStructuralViewElement$(PreprocessSuffix) "Z:/gefri/src/lightweights/gxStructuralViewElement.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/wx_gxLightweightControl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/core_gxComposite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/core_gxComposite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/core_gxComposite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxDcPainter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxDcPainter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxLightweightSystem$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxLightweightSystem$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxPainter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxPainter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxRootViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxRootViewElement$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxViewElement$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxVisualViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxVisualViewElement$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxShape$(DependSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxScaler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxScaler$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxScaler$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxStructuralViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxStructuralViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxStructuralViewElement$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)


