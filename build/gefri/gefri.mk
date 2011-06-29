##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Mac32_Release
ProjectName            :=gefri
ConfigurationName      :=Mac32_Release
IntermediateDirectory  :=./build/Mac32-Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/Development/gefri/build"
ProjectPath            := "/Development/gefri/build/gefri"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Izhaki
Date                   :=06/29/11
CodeLitePath           :="/Users/izhaki/Library/Application Support/codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -dynamiclib -fPIC
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
OutputFile             :=./../../lib/lib$(ProjectName)_mac32.a
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/Development/gefri/build/gefri/gefri.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -O2 $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=no) -arch i386 $(Preprocessors)
C_CmpOptions           := -O2 $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=no) -arch i386 $(Preprocessors)
LinkOptions            :=  -s -arch i386  $(shell $(WX_TOOL) --debug=no --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)../../src 
RcIncludePath          :=
Libs                   :=
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/Applications/CodeLite.app/Contents/SharedSupport/
WX_TOOL:=/Development/wx/wx2.8.12/build-codelite-release/wx-config
Objects=$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) $(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxSructuralViewElement$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix) $(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix) $(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) \
	$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

./build/Mac32-Release:
	@test -d ./build/Mac32-Release || $(MakeDirCommand) ./build/Mac32-Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix): ../../src/adapters/wx/gxLightweightControl.cpp $(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/adapters/wx/gxLightweightControl.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix): ../../src/adapters/wx/gxLightweightControl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) -MF$(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix) -MM "/Development/gefri/src/adapters/wx/gxLightweightControl.cpp"

$(IntermediateDirectory)/wx_gxLightweightControl$(PreprocessSuffix): ../../src/adapters/wx/gxLightweightControl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wx_gxLightweightControl$(PreprocessSuffix) "/Development/gefri/src/adapters/wx/gxLightweightControl.cpp"

$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix): ../../src/core/gxComposite.cpp $(IntermediateDirectory)/core_gxComposite$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/core/gxComposite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_gxComposite$(DependSuffix): ../../src/core/gxComposite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) -MF$(IntermediateDirectory)/core_gxComposite$(DependSuffix) -MM "/Development/gefri/src/core/gxComposite.cpp"

$(IntermediateDirectory)/core_gxComposite$(PreprocessSuffix): ../../src/core/gxComposite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_gxComposite$(PreprocessSuffix) "/Development/gefri/src/core/gxComposite.cpp"

$(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix): ../../src/lightweights/gxDcPainter.cpp $(IntermediateDirectory)/lightweights_gxDcPainter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/gxDcPainter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxDcPainter$(DependSuffix): ../../src/lightweights/gxDcPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxDcPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxDcPainter$(DependSuffix) -MM "/Development/gefri/src/lightweights/gxDcPainter.cpp"

$(IntermediateDirectory)/lightweights_gxDcPainter$(PreprocessSuffix): ../../src/lightweights/gxDcPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxDcPainter$(PreprocessSuffix) "/Development/gefri/src/lightweights/gxDcPainter.cpp"

$(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix): ../../src/lightweights/gxLightweightSystem.cpp $(IntermediateDirectory)/lightweights_gxLightweightSystem$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/gxLightweightSystem.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxLightweightSystem$(DependSuffix): ../../src/lightweights/gxLightweightSystem.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxLightweightSystem$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxLightweightSystem$(DependSuffix) -MM "/Development/gefri/src/lightweights/gxLightweightSystem.cpp"

$(IntermediateDirectory)/lightweights_gxLightweightSystem$(PreprocessSuffix): ../../src/lightweights/gxLightweightSystem.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxLightweightSystem$(PreprocessSuffix) "/Development/gefri/src/lightweights/gxLightweightSystem.cpp"

$(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix): ../../src/lightweights/gxPainter.cpp $(IntermediateDirectory)/lightweights_gxPainter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/gxPainter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxPainter$(DependSuffix): ../../src/lightweights/gxPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxPainter$(DependSuffix) -MM "/Development/gefri/src/lightweights/gxPainter.cpp"

$(IntermediateDirectory)/lightweights_gxPainter$(PreprocessSuffix): ../../src/lightweights/gxPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxPainter$(PreprocessSuffix) "/Development/gefri/src/lightweights/gxPainter.cpp"

$(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix): ../../src/lightweights/gxRootViewElement.cpp $(IntermediateDirectory)/lightweights_gxRootViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/gxRootViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxRootViewElement$(DependSuffix): ../../src/lightweights/gxRootViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxRootViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxRootViewElement$(DependSuffix) -MM "/Development/gefri/src/lightweights/gxRootViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxRootViewElement$(PreprocessSuffix): ../../src/lightweights/gxRootViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxRootViewElement$(PreprocessSuffix) "/Development/gefri/src/lightweights/gxRootViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxSructuralViewElement$(ObjectSuffix): ../../src/lightweights/gxSructuralViewElement.cpp $(IntermediateDirectory)/lightweights_gxSructuralViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/gxSructuralViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxSructuralViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxSructuralViewElement$(DependSuffix): ../../src/lightweights/gxSructuralViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxSructuralViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxSructuralViewElement$(DependSuffix) -MM "/Development/gefri/src/lightweights/gxSructuralViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxSructuralViewElement$(PreprocessSuffix): ../../src/lightweights/gxSructuralViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxSructuralViewElement$(PreprocessSuffix) "/Development/gefri/src/lightweights/gxSructuralViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix): ../../src/lightweights/gxViewElement.cpp $(IntermediateDirectory)/lightweights_gxViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/gxViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxViewElement$(DependSuffix): ../../src/lightweights/gxViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxViewElement$(DependSuffix) -MM "/Development/gefri/src/lightweights/gxViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxViewElement$(PreprocessSuffix): ../../src/lightweights/gxViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxViewElement$(PreprocessSuffix) "/Development/gefri/src/lightweights/gxViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix): ../../src/lightweights/gxVisualViewElement.cpp $(IntermediateDirectory)/lightweights_gxVisualViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/gxVisualViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lightweights_gxVisualViewElement$(DependSuffix): ../../src/lightweights/gxVisualViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lightweights_gxVisualViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/lightweights_gxVisualViewElement$(DependSuffix) -MM "/Development/gefri/src/lightweights/gxVisualViewElement.cpp"

$(IntermediateDirectory)/lightweights_gxVisualViewElement$(PreprocessSuffix): ../../src/lightweights/gxVisualViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lightweights_gxVisualViewElement$(PreprocessSuffix) "/Development/gefri/src/lightweights/gxVisualViewElement.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix): ../../src/lightweights/shapes/gxRectangle.cpp $(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/shapes/gxRectangle.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix): ../../src/lightweights/shapes/gxRectangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix) -MM "/Development/gefri/src/lightweights/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix): ../../src/lightweights/shapes/gxRectangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix) "/Development/gefri/src/lightweights/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix): ../../src/lightweights/shapes/gxShape.cpp $(IntermediateDirectory)/shapes_gxShape$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/lightweights/shapes/gxShape.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxShape$(DependSuffix): ../../src/lightweights/shapes/gxShape.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxShape$(DependSuffix) -MM "/Development/gefri/src/lightweights/shapes/gxShape.cpp"

$(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix): ../../src/lightweights/shapes/gxShape.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix) "/Development/gefri/src/lightweights/shapes/gxShape.cpp"


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
	$(RM) $(IntermediateDirectory)/lightweights_gxSructuralViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxSructuralViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lightweights_gxSructuralViewElement$(PreprocessSuffix)
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
	$(RM) $(OutputFile)


