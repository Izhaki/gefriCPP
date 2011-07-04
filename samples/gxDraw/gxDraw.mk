##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Linux32_Release
ProjectName            :=gxDraw
ConfigurationName      :=Linux32_Release
IntermediateDirectory  :=./build/Linux32-Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/Development/gefri/build"
ProjectPath            := "/Development/gefri/samples/gxDraw"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Roey Izhaki
Date                   :=04/07/11
CodeLitePath           :="/home/roey/.codelite"
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/Development/gefri/samples/gxDraw/gxDraw.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -O2 $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
C_CmpOptions           := -O2 $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
LinkOptions            :=  -mwindows  $(shell wx-config --debug=no --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)$(WorkspacePath)/../src 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)gefri_linux32 
LibPath                := $(LibraryPathSwitch)$(WorkspacePath)/../lib 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
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
	@test -d ./build/Linux32-Release || $(MakeDirCommand) ./build/Linux32-Release

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


