import os
import shutil
import sys

pwd = os.getcwd()
print(pwd + "\n")
os.chdir(os.path.dirname(sys.argv[0]))

#get the list of files ending in png
for currentFile in [png for png in os.listdir('./') if  png.endswith(".png")]:
 #delete the file
 os.remove(currentFile)
 
#get the list of files ending in tga
for currentFile in [tga for tga in os.listdir('./') if  tga.endswith(".tga")]:
 #delete the file
 os.remove(currentFile)
 
#get the list of files ending in bmfc
for currentFile in [bmfc for bmfc in os.listdir('./') if  bmfc.endswith(".bmfc")]:
 #delete the file
 os.remove(currentFile)
 
  #get the list of files ending in fnt
for currentFile in [fnt for fnt in os.listdir('./') if  fnt.endswith(".fnt")]:
 #delete the file
 os.remove(currentFile)
 
#Run the ODS Manipulator
command = 'FontCreator.exe'
os.system(command)

#get the list of files ending in bmfc
for currentFile in [bmfc for bmfc in os.listdir('./') if  bmfc.endswith(".bmfc")]:
#create a command to run bmFont.exe using the current bmfc and saving it as a fnt file
 command = '"bmfont.exe" -c ' + currentFile + ' -o ' + currentFile.replace(".bmfc", ".fnt")
 os.system(command)
 os.remove(currentFile)

print("Path at terminal when executing this file")
#get the list of files ending in png
for currentFile in [png for png in os.listdir('./') if  png.endswith(".png")]:
	#get The input and output file names
	inFile = './' + currentFile
	outFile = '../../../../../Media/Assets/Fonts/' + currentFile
	#copy the file to the sprites objects data directory
	shutil.move(inFile, outFile)

#get the list of files ending in tga
for currentFile in [tga for tga in os.listdir('./') if  tga.endswith(".tga")]:
	#get The input and output file names
	inFile = './' + currentFile
	outFile = '../../../../../Media/Assets/Fonts/' + currentFile
	#copy the file to the sprites objects data directory
	shutil.move(inFile, outFile)
	
#get the list of files ending in fnt
for currentFile in [fnt for fnt in os.listdir('./') if  fnt.endswith(".fnt")]:
	#get The input and output file names
	inFile = './' + currentFile
	outFile = '../../../../../Media/Assets/Fonts/' + currentFile
	#copy the file to the sprites objects data directory
	shutil.move(inFile, outFile)
	
#get the list of files ending in loc
for currentFile in [loc for loc in os.listdir('./') if  loc.endswith(".loc")]:
	#get The input and output file names
	inFile = './' + currentFile
	outFile = '../../../../../Media/Assets/Localization/' + currentFile
	#copy the file to the build/win32 directory
	shutil.move(inFile, outFile)
