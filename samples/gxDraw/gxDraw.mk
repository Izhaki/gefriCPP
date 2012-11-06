##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Mac32_Debug
ProjectName            :=gxDraw
ConfigurationName      :=Mac32_Debug
WorkspacePath          := "/Volumes/Blackstore/Development/gefri/build"
ProjectPath            := "/Volumes/Blackstore/Development/gefri/samples/gxDraw"
IntermediateDirectory  :=./build/Mac32-Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Izhaki
Date                   :=2012-11-06
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).app/Contents/MacOS/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/Volumes/Blackstore/Development/gefri/samples/gxDraw/gxDraw.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -mwindows  $(shell $(WX_TOOL) --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)$(WorkspacePath)/../src 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gefri_mac32d 
ArLibs                 :=  "gefri_mac32d.a" 
LibPath                := $(LibraryPathSwitch)$(WorkspacePath)/../lib 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=yes)  $(Preprocessors)
CFLAGS   :=  -g $(shell $(WX_TOOL) --cxxflags --unicode=yes --debug=yes)  $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/Applications/CodeLite.app/Contents/SharedSupport/
WX_TOOL:=/Volumes/Blackstore/Development/wx/wx2.9.4/build-debug-mac/wx-config
Objects=$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IntermediateDirectory)/src_myFrame$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/samples/gxDraw/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/samples/gxDraw/src/main.cpp"

$(IntermediateDirectory)/src_main$(PreprocessSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/samples/gxDraw/src/main.cpp"

$(IntermediateDirectory)/src_myFrame$(ObjectSuffix): src/myFrame.cpp $(IntermediateDirectory)/src_myFrame$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Volumes/Blackstore/Development/gefri/samples/gxDraw/src/myFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_myFrame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_myFrame$(DependSuffix): src/myFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_myFrame$(ObjectSuffix) -MF$(IntermediateDirectory)/src_myFrame$(DependSuffix) -MM "/Volumes/Blackstore/Development/gefri/samples/gxDraw/src/myFrame.cpp"

$(IntermediateDirectory)/src_myFrame$(PreprocessSuffix): src/myFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_myFrame$(PreprocessSuffix) "/Volumes/Blackstore/Development/gefri/samples/gxDraw/src/myFrame.cpp"


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
	$(RM) "/Volumes/Blackstore/Development/gefri/build/.build-mac32_debug/gxDraw"


