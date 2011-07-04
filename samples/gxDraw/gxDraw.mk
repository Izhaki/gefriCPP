##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Mac32_Debug
ProjectName            :=gxDraw
ConfigurationName      :=Mac32_Debug
IntermediateDirectory  :=./build/Mac32-Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/Development/gefri/build"
ProjectPath            := "/Development/gefri/samples/gxDraw"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Izhaki
Date                   :=07/05/11
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).app/Contents/MacOS/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/Development/gefri/samples/gxDraw/gxDraw.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=yes) -arch i386 $(Preprocessors)
C_CmpOptions           := -g $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=yes) -arch i386 $(Preprocessors)
LinkOptions            :=  -mwindows -arch i386  $(shell $(WX_TOOL) --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)$(WorkspacePath)/../src 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)gefri_mac32d 
LibPath                := $(LibraryPathSwitch)$(WorkspacePath)/../lib 


##
## User defined environment variables
##
CodeLiteDir:=/Applications/CodeLite.app/Contents/SharedSupport/
WX_TOOL:=/Development/wx/wx2.8.12/build-codelite-debug/wx-config
Objects=$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IntermediateDirectory)/src_myFrame$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d ./build/Mac32-Debug || $(MakeDirCommand) ./build/Mac32-Debug
PrePreBuild: $(IntermediateDirectory)/$(ProjectName).app/Contents/Info.plist $(IntermediateDirectory)/$(ProjectName).app/Contents/Resources/gxDraw.icns
## rule to copy the Info.plist file into the bundle
$(IntermediateDirectory)/$(ProjectName).app/Contents/Info.plist: Info.plist
	mkdir -p '$(IntermediateDirectory)/$(ProjectName).app/Contents' && cp -f Info.plist '$(IntermediateDirectory)/$(ProjectName).app/Contents/Info.plist'
## rule to copy the icon file into the bundle
$(IntermediateDirectory)/$(ProjectName).app/Contents/Resources/gxDraw.icns: gxDraw.icns
	mkdir -p '$(IntermediateDirectory)/$(ProjectName).app/Contents/Resources/' && cp -f gxDraw.icns '$(IntermediateDirectory)/$(ProjectName).app/Contents/Resources/gxDraw.icns'

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_main$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/samples/gxDraw/src/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main$(DependSuffix): src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main$(DependSuffix) -MM "/Development/gefri/samples/gxDraw/src/main.cpp"

$(IntermediateDirectory)/src_main$(PreprocessSuffix): src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main$(PreprocessSuffix) "/Development/gefri/samples/gxDraw/src/main.cpp"

$(IntermediateDirectory)/src_myFrame$(ObjectSuffix): src/myFrame.cpp $(IntermediateDirectory)/src_myFrame$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Development/gefri/samples/gxDraw/src/myFrame.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_myFrame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_myFrame$(DependSuffix): src/myFrame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_myFrame$(ObjectSuffix) -MF$(IntermediateDirectory)/src_myFrame$(DependSuffix) -MM "/Development/gefri/samples/gxDraw/src/myFrame.cpp"

$(IntermediateDirectory)/src_myFrame$(PreprocessSuffix): src/myFrame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_myFrame$(PreprocessSuffix) "/Development/gefri/samples/gxDraw/src/myFrame.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_myFrame$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_myFrame$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_myFrame$(PreprocessSuffix)
	$(RM) $(OutputFile)


