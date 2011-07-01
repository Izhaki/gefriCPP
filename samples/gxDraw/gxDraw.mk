##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Win32_Debug
ProjectName            :=gxDraw
ConfigurationName      :=Win32_Debug
IntermediateDirectory  :=./build/Win32-Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "Z:\gefri\build"
ProjectPath            := "Z:\gefri\samples\gxDraw"
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Z:\gefri\samples\gxDraw\gxDraw.txt"
MakeDirCommand         :=makedir
CmpOptions             := -g $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
C_CmpOptions           := -g $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
RcCmpOptions           := $(shell wx-config --rcflags)
RcCompilerName         :=windres
LinkOptions            :=  $(shell wx-config --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch)$(WorkspacePath)/../src 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)gefri_msw32d 
LibPath                := $(LibraryPathSwitch)$(WorkspacePath)/../lib 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
WXWIN:=C:\wxWidgets-2.8.12
PATH:=$(WXWIN)\lib\gcc_lib;$(PATH)
WXCFG:=gcc_lib\mswu
Objects=$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IntermediateDirectory)/src_myFrame$(ObjectSuffix) $(IntermediateDirectory)/gxDraw.rc$(ObjectSuffix) 

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
	@$(MakeDirCommand) "./build/Win32-Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_main$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/samples/gxDraw/src/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main$(DependSuffix): src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main$(DependSuffix) -MM "Z:/gefri/samples/gxDraw/src/main.cpp"

$(IntermediateDirectory)/src_main$(PreprocessSuffix): src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main$(PreprocessSuffix) "Z:/gefri/samples/gxDraw/src/main.cpp"

$(IntermediateDirectory)/src_myFrame$(ObjectSuffix): src/myFrame.cpp $(IntermediateDirectory)/src_myFrame$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "Z:/gefri/samples/gxDraw/src/myFrame.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_myFrame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_myFrame$(DependSuffix): src/myFrame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_myFrame$(ObjectSuffix) -MF$(IntermediateDirectory)/src_myFrame$(DependSuffix) -MM "Z:/gefri/samples/gxDraw/src/myFrame.cpp"

$(IntermediateDirectory)/src_myFrame$(PreprocessSuffix): src/myFrame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_myFrame$(PreprocessSuffix) "Z:/gefri/samples/gxDraw/src/myFrame.cpp"

$(IntermediateDirectory)/gxDraw.rc$(ObjectSuffix): gxDraw.rc
	$(RcCompilerName) -i "Z:/gefri/samples/gxDraw/gxDraw.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/gxDraw.rc$(ObjectSuffix) $(RcIncludePath)

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
	$(RM) $(IntermediateDirectory)/gxDraw.rc$(ObjectSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe


