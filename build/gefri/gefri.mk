##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Mac32_Debug
ProjectName            :=gefri
ConfigurationName      :=Mac32_Debug
IntermediateDirectory  :=./build/Mac32-Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/Development/gefri/build"
ProjectPath            := "/Development/gefri/build/gefri"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Izhaki
Date                   :=08/10/11
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
OutputFile             :=./../../lib/lib$(ProjectName)_mac32d.a
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/Development/gefri/build/gefri/gefri.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=yes) -arch i386 $(Preprocessors)
C_CmpOptions           := -g $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=yes) -arch i386 $(Preprocessors)
LinkOptions            :=  -arch i386  $(shell $(WX_TOOL) --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)../../src 
RcIncludePath          :=
Libs                   :=
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/Applications/CodeLite.app/Contents/SharedSupport/
WX_TOOL:=/Development/wx/wx2.8.12/build-codelite-debug/wx-config
Objects=$(IntermediateDirectory)/wx_gxLightweightControl$(ObjectSuffix) $(IntermediateDirectory)/core_gxComposite$(ObjectSuffix) $(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix) $(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix) $(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix) $(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix) $(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix) $(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix) $(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix) $(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix) \
	$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix) $(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix) $(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix) $(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) $(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) $(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix) $(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix) $(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix) $(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix) $(IntermediateDirectory)/view_gxPainter$(ObjectSuffix) \
	

##
## Main Build Targets 
##
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	$(ArchiveTool) $(ArchiveOutputSwitch)$(OutputFile) $(Objects)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

./build/Mac32-Debug:
	@test -d ./build/Mac32-Debug || $(MakeDirCommand) ./build/Mac32-Debug

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

$(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix): ../../src/core/geometry/gxRect.cpp $(IntermediateDirectory)/geometry_gxRect$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/core/geometry/gxRect.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/geometry_gxRect$(DependSuffix): ../../src/core/geometry/gxRect.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/geometry_gxRect$(ObjectSuffix) -MF$(IntermediateDirectory)/geometry_gxRect$(DependSuffix) -MM "/Development/gefri/src/core/geometry/gxRect.cpp"

$(IntermediateDirectory)/geometry_gxRect$(PreprocessSuffix): ../../src/core/geometry/gxRect.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/geometry_gxRect$(PreprocessSuffix) "/Development/gefri/src/core/geometry/gxRect.cpp"

$(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix): ../../src/core/gxObserverList.cpp $(IntermediateDirectory)/core_gxObserverList$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/core/gxObserverList.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_gxObserverList$(DependSuffix): ../../src/core/gxObserverList.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_gxObserverList$(ObjectSuffix) -MF$(IntermediateDirectory)/core_gxObserverList$(DependSuffix) -MM "/Development/gefri/src/core/gxObserverList.cpp"

$(IntermediateDirectory)/core_gxObserverList$(PreprocessSuffix): ../../src/core/gxObserverList.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_gxObserverList$(PreprocessSuffix) "/Development/gefri/src/core/gxObserverList.cpp"

$(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix): ../../src/view/gxDcPainter.cpp $(IntermediateDirectory)/view_gxDcPainter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/gxDcPainter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxDcPainter$(DependSuffix): ../../src/view/gxDcPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxDcPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxDcPainter$(DependSuffix) -MM "/Development/gefri/src/view/gxDcPainter.cpp"

$(IntermediateDirectory)/view_gxDcPainter$(PreprocessSuffix): ../../src/view/gxDcPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxDcPainter$(PreprocessSuffix) "/Development/gefri/src/view/gxDcPainter.cpp"

$(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix): ../../src/view/gxLightweightSystem.cpp $(IntermediateDirectory)/view_gxLightweightSystem$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/gxLightweightSystem.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxLightweightSystem$(DependSuffix): ../../src/view/gxLightweightSystem.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxLightweightSystem$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxLightweightSystem$(DependSuffix) -MM "/Development/gefri/src/view/gxLightweightSystem.cpp"

$(IntermediateDirectory)/view_gxLightweightSystem$(PreprocessSuffix): ../../src/view/gxLightweightSystem.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxLightweightSystem$(PreprocessSuffix) "/Development/gefri/src/view/gxLightweightSystem.cpp"

$(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix): ../../src/view/managers/gxZoomManager.cpp $(IntermediateDirectory)/managers_gxZoomManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/managers/gxZoomManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/managers_gxZoomManager$(DependSuffix): ../../src/view/managers/gxZoomManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/managers_gxZoomManager$(ObjectSuffix) -MF$(IntermediateDirectory)/managers_gxZoomManager$(DependSuffix) -MM "/Development/gefri/src/view/managers/gxZoomManager.cpp"

$(IntermediateDirectory)/managers_gxZoomManager$(PreprocessSuffix): ../../src/view/managers/gxZoomManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/managers_gxZoomManager$(PreprocessSuffix) "/Development/gefri/src/view/managers/gxZoomManager.cpp"

$(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix): ../../src/view/managers/gxScrollManager.cpp $(IntermediateDirectory)/managers_gxScrollManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/managers/gxScrollManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/managers_gxScrollManager$(DependSuffix): ../../src/view/managers/gxScrollManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/managers_gxScrollManager$(ObjectSuffix) -MF$(IntermediateDirectory)/managers_gxScrollManager$(DependSuffix) -MM "/Development/gefri/src/view/managers/gxScrollManager.cpp"

$(IntermediateDirectory)/managers_gxScrollManager$(PreprocessSuffix): ../../src/view/managers/gxScrollManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/managers_gxScrollManager$(PreprocessSuffix) "/Development/gefri/src/view/managers/gxScrollManager.cpp"

$(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix): ../../src/view/elements/gxRootViewElement.cpp $(IntermediateDirectory)/elements_gxRootViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/gxRootViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxRootViewElement$(DependSuffix): ../../src/view/elements/gxRootViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxRootViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxRootViewElement$(DependSuffix) -MM "/Development/gefri/src/view/elements/gxRootViewElement.cpp"

$(IntermediateDirectory)/elements_gxRootViewElement$(PreprocessSuffix): ../../src/view/elements/gxRootViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxRootViewElement$(PreprocessSuffix) "/Development/gefri/src/view/elements/gxRootViewElement.cpp"

$(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix): ../../src/view/elements/gxScaler.cpp $(IntermediateDirectory)/elements_gxScaler$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/gxScaler.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxScaler$(DependSuffix): ../../src/view/elements/gxScaler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxScaler$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxScaler$(DependSuffix) -MM "/Development/gefri/src/view/elements/gxScaler.cpp"

$(IntermediateDirectory)/elements_gxScaler$(PreprocessSuffix): ../../src/view/elements/gxScaler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxScaler$(PreprocessSuffix) "/Development/gefri/src/view/elements/gxScaler.cpp"

$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix): ../../src/view/elements/gxStructuralViewElement.cpp $(IntermediateDirectory)/elements_gxStructuralViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/gxStructuralViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxStructuralViewElement$(DependSuffix): ../../src/view/elements/gxStructuralViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxStructuralViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxStructuralViewElement$(DependSuffix) -MM "/Development/gefri/src/view/elements/gxStructuralViewElement.cpp"

$(IntermediateDirectory)/elements_gxStructuralViewElement$(PreprocessSuffix): ../../src/view/elements/gxStructuralViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxStructuralViewElement$(PreprocessSuffix) "/Development/gefri/src/view/elements/gxStructuralViewElement.cpp"

$(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix): ../../src/view/elements/gxViewElement.cpp $(IntermediateDirectory)/elements_gxViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/gxViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxViewElement$(DependSuffix): ../../src/view/elements/gxViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxViewElement$(DependSuffix) -MM "/Development/gefri/src/view/elements/gxViewElement.cpp"

$(IntermediateDirectory)/elements_gxViewElement$(PreprocessSuffix): ../../src/view/elements/gxViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxViewElement$(PreprocessSuffix) "/Development/gefri/src/view/elements/gxViewElement.cpp"

$(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix): ../../src/view/elements/gxVisualViewElement.cpp $(IntermediateDirectory)/elements_gxVisualViewElement$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/gxVisualViewElement.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxVisualViewElement$(DependSuffix): ../../src/view/elements/gxVisualViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxVisualViewElement$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxVisualViewElement$(DependSuffix) -MM "/Development/gefri/src/view/elements/gxVisualViewElement.cpp"

$(IntermediateDirectory)/elements_gxVisualViewElement$(PreprocessSuffix): ../../src/view/elements/gxVisualViewElement.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxVisualViewElement$(PreprocessSuffix) "/Development/gefri/src/view/elements/gxVisualViewElement.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix): ../../src/view/elements/shapes/gxRectangle.cpp $(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/shapes/gxRectangle.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix): ../../src/view/elements/shapes/gxRectangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxRectangle$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxRectangle$(DependSuffix) -MM "/Development/gefri/src/view/elements/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix): ../../src/view/elements/shapes/gxRectangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxRectangle$(PreprocessSuffix) "/Development/gefri/src/view/elements/shapes/gxRectangle.cpp"

$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix): ../../src/view/elements/shapes/gxShape.cpp $(IntermediateDirectory)/shapes_gxShape$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/shapes/gxShape.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes_gxShape$(DependSuffix): ../../src/view/elements/shapes/gxShape.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes_gxShape$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes_gxShape$(DependSuffix) -MM "/Development/gefri/src/view/elements/shapes/gxShape.cpp"

$(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix): ../../src/view/elements/shapes/gxShape.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes_gxShape$(PreprocessSuffix) "/Development/gefri/src/view/elements/shapes/gxShape.cpp"

$(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix): ../../src/view/elements/gxScroller.cpp $(IntermediateDirectory)/elements_gxScroller$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/gxScroller.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxScroller$(DependSuffix): ../../src/view/elements/gxScroller.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxScroller$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxScroller$(DependSuffix) -MM "/Development/gefri/src/view/elements/gxScroller.cpp"

$(IntermediateDirectory)/elements_gxScroller$(PreprocessSuffix): ../../src/view/elements/gxScroller.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxScroller$(PreprocessSuffix) "/Development/gefri/src/view/elements/gxScroller.cpp"

$(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix): ../../src/view/elements/gxRuler.cpp $(IntermediateDirectory)/elements_gxRuler$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/elements/gxRuler.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/elements_gxRuler$(DependSuffix): ../../src/view/elements/gxRuler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/elements_gxRuler$(ObjectSuffix) -MF$(IntermediateDirectory)/elements_gxRuler$(DependSuffix) -MM "/Development/gefri/src/view/elements/gxRuler.cpp"

$(IntermediateDirectory)/elements_gxRuler$(PreprocessSuffix): ../../src/view/elements/gxRuler.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/elements_gxRuler$(PreprocessSuffix) "/Development/gefri/src/view/elements/gxRuler.cpp"

$(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix): ../../src/view/gxDivProvider.cpp $(IntermediateDirectory)/view_gxDivProvider$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/gxDivProvider.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxDivProvider$(DependSuffix): ../../src/view/gxDivProvider.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxDivProvider$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxDivProvider$(DependSuffix) -MM "/Development/gefri/src/view/gxDivProvider.cpp"

$(IntermediateDirectory)/view_gxDivProvider$(PreprocessSuffix): ../../src/view/gxDivProvider.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxDivProvider$(PreprocessSuffix) "/Development/gefri/src/view/gxDivProvider.cpp"

$(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix): ../../src/view/gxViewUnit.cpp $(IntermediateDirectory)/view_gxViewUnit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/gxViewUnit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxViewUnit$(DependSuffix): ../../src/view/gxViewUnit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxViewUnit$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxViewUnit$(DependSuffix) -MM "/Development/gefri/src/view/gxViewUnit.cpp"

$(IntermediateDirectory)/view_gxViewUnit$(PreprocessSuffix): ../../src/view/gxViewUnit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxViewUnit$(PreprocessSuffix) "/Development/gefri/src/view/gxViewUnit.cpp"

$(IntermediateDirectory)/view_gxPainter$(ObjectSuffix): ../../src/view/gxPainter.cpp $(IntermediateDirectory)/view_gxPainter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/src/view/gxPainter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/view_gxPainter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_gxPainter$(DependSuffix): ../../src/view/gxPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_gxPainter$(ObjectSuffix) -MF$(IntermediateDirectory)/view_gxPainter$(DependSuffix) -MM "/Development/gefri/src/view/gxPainter.cpp"

$(IntermediateDirectory)/view_gxPainter$(PreprocessSuffix): ../../src/view/gxPainter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_gxPainter$(PreprocessSuffix) "/Development/gefri/src/view/gxPainter.cpp"


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


