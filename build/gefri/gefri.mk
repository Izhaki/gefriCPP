##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Mac32_Release
ProjectName            :=gefri
ConfigurationName      :=Mac32_Release
WorkspacePath          := "/Volumes/Blackstore/Development/gefri/build"
ProjectPath            := "/Volumes/Blackstore/Development/gefri/build/gefri"
IntermediateDirectory  :=./build/Mac32-Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Izhaki
Date                   :=2012-10-22
CodeLitePath           :="/Users/izhaki/Library/Application Support/codelite"
LinkerName             :=g++
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
OutputFile             :=./../../lib/lib$(ProjectName)_mac32.a
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/Volumes/Blackstore/Development/gefri/build/gefri/gefri.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -s $(shell $(WX_TOOL) --debug=no --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)../../src 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=no)  $(Preprocessors)
CFLAGS   :=  -O2 $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=no)  $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/Applications/CodeLite.app/Contents/SharedSupport/
WX_TOOL:=/Volumes/Blackstore/Development/wx/wx2.9.4/build-release-mac/wx-config
Objects=$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) $(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) $(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix) $(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix) $(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix) $(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix) $(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix) $(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix) $(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix) $(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix) \
	$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix) $(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix) $(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix) $(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) $(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) $(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix) $(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix) $(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix) $(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix) $(IntermediateDirectory)/view_gxPainter$(ObjectSuffix) \
	

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) $(Objects) $(ArLibs)
	@$(MakeDirCommand) "/Volumes/Blackstore/Development/gefri/build/.build-mac32_release"
	@echo rebuilt > "/Volumes/Blackstore/Development/gefri/build/.build-mac32_release/gefri"

./build/Mac32-Release:
	@test -d ./build/Mac32-Release || $(MakeDirCommand) ./build/Mac32-Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix): ../../src/adapters/wx/gxLightweightControl.cpp $(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/adapters/wx/gxLightweightControl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix): ../../src/adapters/wx/gxLightweightControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) -MF$(IntermediateDirectory)/wx_gxLightweightControl$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/adapters/wx/gxLightweightControl.cpp"

$(IntermediateDirectory)/wx_gxLightweightControl$(PreprocessSuffix): ../../src/adapters/wx/gxLightweightControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wx_gxLightweightControl$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/adapters/wx/gxLightweightControl.cpp"

$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix): ../../src/core/gxComposite.cpp $(IntermediateDirectory)/core_gxComposite$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/core/gxComposite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_gxComposite$(DependSuffix): ../../src/core/gxComposite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) -MF$(IntermediateDirectory)/core_gxComposite$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/core/gxComposite.cpp"

$(IntermediateDirectory)/core_gxComposite$(PreprocessSuffix): ../../src/core/gxComposite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_gxComposite$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/core/gxComposite.cpp"

$(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix): ../../src/core/geometry/gxRect.cpp $(IntermediateDirectory)/geometry_gxRect$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/core/geometry/gxRect.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/geometry_gxRect$(DependSuffix): ../../src/core/geometry/gxRect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix) -MF$(IntermediateDirectory)/geometry_gxRect$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/core/geometry/gxRect.cpp"

$(IntermediateDirectory)/geometry_gxRect$(PreprocessSuffix): ../../src/core/geometry/gxRect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/geometry_gxRect$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/core/geometry/gxRect.cpp"

$(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix): ../../src/core/gxObserverList.cpp $(IntermediateDirectory)/core_gxObserverList$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/core/gxObserverList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_gxObserverList$(DependSuffix): ../../src/core/gxObserverList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix) -MF$(IntermediateDirectory)/core_gxObserverList$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/core/gxObserverList.cpp"

$(IntermediateDirectory)/core_gxObserverList$(PreprocessSuffix): ../../src/core/gxObserverList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_gxObserverList$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/core/gxObserverList.cpp"

$(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix): ../../src/view/gxDcPainter.cpp $(IntermediateDirectory)/view_gxDcPainter$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/gxDcPainter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxDcPainter$(DependSuffix): ../../src/view/gxDcPainter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxDcPainter$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/gxDcPainter.cpp"

$(IntermediateDirectory)/view_gxDcPainter$(PreprocessSuffix): ../../src/view/gxDcPainter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxDcPainter$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/gxDcPainter.cpp"

$(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix): ../../src/view/gxLightweightSystem.cpp $(IntermediateDirectory)/view_gxLightweightSystem$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/gxLightweightSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxLightweightSystem$(DependSuffix): ../../src/view/gxLightweightSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxLightweightSystem$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/gxLightweightSystem.cpp"

$(IntermediateDirectory)/view_gxLightweightSystem$(PreprocessSuffix): ../../src/view/gxLightweightSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxLightweightSystem$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/gxLightweightSystem.cpp"

$(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix): ../../src/view/managers/gxZoomManager.cpp $(IntermediateDirectory)/managers_gxZoomManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/managers/gxZoomManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/managers_gxZoomManager$(DependSuffix): ../../src/view/managers/gxZoomManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix) -MF$(IntermediateDirectory)/managers_gxZoomManager$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/managers/gxZoomManager.cpp"

$(IntermediateDirectory)/managers_gxZoomManager$(PreprocessSuffix): ../../src/view/managers/gxZoomManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/managers_gxZoomManager$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/managers/gxZoomManager.cpp"

$(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix): ../../src/view/managers/gxScrollManager.cpp $(IntermediateDirectory)/managers_gxScrollManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/managers/gxScrollManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/managers_gxScrollManager$(DependSuffix): ../../src/view/managers/gxScrollManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix) -MF$(IntermediateDirectory)/managers_gxScrollManager$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/managers/gxScrollManager.cpp"

$(IntermediateDirectory)/managers_gxScrollManager$(PreprocessSuffix): ../../src/view/managers/gxScrollManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/managers_gxScrollManager$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/managers/gxScrollManager.cpp"

$(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix): ../../src/view/elements/gxRootViewElement.cpp $(IntermediateDirectory)/elements_gxRootViewElement$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxRootViewElement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxRootViewElement$(DependSuffix): ../../src/view/elements/gxRootViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxRootViewElement$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/gxRootViewElement.cpp"

$(IntermediateDirectory)/elements_gxRootViewElement$(PreprocessSuffix): ../../src/view/elements/gxRootViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxRootViewElement$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxRootViewElement.cpp"

$(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix): ../../src/view/elements/gxScaler.cpp $(IntermediateDirectory)/elements_gxScaler$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxScaler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxScaler$(DependSuffix): ../../src/view/elements/gxScaler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxScaler$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/gxScaler.cpp"

$(IntermediateDirectory)/elements_gxScaler$(PreprocessSuffix): ../../src/view/elements/gxScaler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxScaler$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxScaler.cpp"

$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix): ../../src/view/elements/gxStructuralViewElement.cpp $(IntermediateDirectory)/elements_gxStructuralViewElement$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxStructuralViewElement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxStructuralViewElement$(DependSuffix): ../../src/view/elements/gxStructuralViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxStructuralViewElement$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/gxStructuralViewElement.cpp"

$(IntermediateDirectory)/elements_gxStructuralViewElement$(PreprocessSuffix): ../../src/view/elements/gxStructuralViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxStructuralViewElement$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxStructuralViewElement.cpp"

$(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix): ../../src/view/elements/gxViewElement.cpp $(IntermediateDirectory)/elements_gxViewElement$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxViewElement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxViewElement$(DependSuffix): ../../src/view/elements/gxViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxViewElement$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/gxViewElement.cpp"

$(IntermediateDirectory)/elements_gxViewElement$(PreprocessSuffix): ../../src/view/elements/gxViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxViewElement$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxViewElement.cpp"

$(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix): ../../src/view/elements/gxVisualViewElement.cpp $(IntermediateDirectory)/elements_gxVisualViewElement$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxVisualViewElement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxVisualViewElement$(DependSuffix): ../../src/view/elements/gxVisualViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxVisualViewElement$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/gxVisualViewElement.cpp"

$(IntermediateDirectory)/elements_gxVisualViewElement$(PreprocessSuffix): ../../src/view/elements/gxVisualViewElement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxVisualViewElement$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxVisualViewElement.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix): ../../src/view/elements/shapes/gxRectangle.cpp $(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/shapes/gxRectangle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix): ../../src/view/elements/shapes/gxRectangle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix): ../../src/view/elements/shapes/gxRectangle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix): ../../src/view/elements/shapes/gxShape.cpp $(IntermediateDirectory)/shapes_gxShape$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/shapes/gxShape.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxShape$(DependSuffix): ../../src/view/elements/shapes/gxShape.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxShape$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/shapes/gxShape.cpp"

$(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix): ../../src/view/elements/shapes/gxShape.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/shapes/gxShape.cpp"

$(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix): ../../src/view/elements/gxScroller.cpp $(IntermediateDirectory)/elements_gxScroller$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxScroller.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxScroller$(DependSuffix): ../../src/view/elements/gxScroller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxScroller$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/gxScroller.cpp"

$(IntermediateDirectory)/elements_gxScroller$(PreprocessSuffix): ../../src/view/elements/gxScroller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxScroller$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxScroller.cpp"

$(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix): ../../src/view/elements/gxRuler.cpp $(IntermediateDirectory)/elements_gxRuler$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxRuler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxRuler$(DependSuffix): ../../src/view/elements/gxRuler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxRuler$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/elements/gxRuler.cpp"

$(IntermediateDirectory)/elements_gxRuler$(PreprocessSuffix): ../../src/view/elements/gxRuler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxRuler$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/elements/gxRuler.cpp"

$(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix): ../../src/view/gxDivProvider.cpp $(IntermediateDirectory)/view_gxDivProvider$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/gxDivProvider.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxDivProvider$(DependSuffix): ../../src/view/gxDivProvider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxDivProvider$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/gxDivProvider.cpp"

$(IntermediateDirectory)/view_gxDivProvider$(PreprocessSuffix): ../../src/view/gxDivProvider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxDivProvider$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/gxDivProvider.cpp"

$(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix): ../../src/view/gxViewUnit.cpp $(IntermediateDirectory)/view_gxViewUnit$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/gxViewUnit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxViewUnit$(DependSuffix): ../../src/view/gxViewUnit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxViewUnit$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/gxViewUnit.cpp"

$(IntermediateDirectory)/view_gxViewUnit$(PreprocessSuffix): ../../src/view/gxViewUnit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxViewUnit$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/gxViewUnit.cpp"

$(IntermediateDirectory)/view_gxPainter$(ObjectSuffix): ../../src/view/gxPainter.cpp $(IntermediateDirectory)/view_gxPainter$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/src/view/gxPainter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_gxPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxPainter$(DependSuffix): ../../src/view/gxPainter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxPainter$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/src/view/gxPainter.cpp"

$(IntermediateDirectory)/view_gxPainter$(PreprocessSuffix): ../../src/view/gxPainter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxPainter$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/src/view/gxPainter.cpp"


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
	$(RM) $(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/geometry_gxRect$(DependSuffix)
	$(RM) $(IntermediateDirectory)/geometry_gxRect$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/core_gxObserverList$(DependSuffix)
	$(RM) $(IntermediateDirectory)/core_gxObserverList$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/view_gxDcPainter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/view_gxDcPainter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/view_gxLightweightSystem$(DependSuffix)
	$(RM) $(IntermediateDirectory)/view_gxLightweightSystem$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/managers_gxZoomManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/managers_gxZoomManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/managers_gxScrollManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/managers_gxScrollManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxRootViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxRootViewElement$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxScaler$(DependSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxScaler$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxStructuralViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxStructuralViewElement$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxViewElement$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxVisualViewElement$(DependSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxVisualViewElement$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxShape$(DependSuffix)
	$(RM) $(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxScroller$(DependSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxScroller$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxRuler$(DependSuffix)
	$(RM) $(IntermediateDirectory)/elements_gxRuler$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/view_gxDivProvider$(DependSuffix)
	$(RM) $(IntermediateDirectory)/view_gxDivProvider$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/view_gxViewUnit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/view_gxViewUnit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/view_gxPainter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/view_gxPainter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/view_gxPainter$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/Volumes/Blackstore/Development/gefri/build/.build-mac32_release/gefri"


