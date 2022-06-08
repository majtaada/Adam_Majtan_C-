#include "CFileReader.hpp" 


#define FORMAT_LEN 4

void CFileReader::readDirectory( std::string fileType) const
{
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
      std::string fileDir = entry.path();
      fileDir.erase(0,path.size());
      if ( fileDir.substr(fileDir.size()-FORMAT_LEN,4) == fileType)
      std::cout << fileDir << std::endl;
    }

}

void CFileReader::print(void) const
{
    std::cout << "Zadaj image name .png, ktory chces nacitat" << std::endl;
    readDirectory(".png");
    std::cout << space << space << space << std::endl;
    std::cout << "!! AK SA TI OBRAZOK ZOBRAZI ZLE , SKUS ODZOOMOVAT ALEBO POUZIT EFEKT KONVOLUCE !!" << std::endl;
    std::cout << space << space << space << std::endl;
}

std::string CFileReader::readInput (  ) const
{
    std::string fileName;
    std::string fileRead;
    print();
    std::cin  >> fileRead;
    fileName = path + fileRead;
    std::fstream file( fileName );
    std::cout << fileName << std::endl;
    if(!checkIfFileValid(fileName))
      throw std::invalid_argument("Nefunkcny image, skus iny");
    
    return fileName;
}

bool CFileReader::checkIfFileValid(const std::string &name) const
{
  if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

void CFileReader::initializeAsciiTransition ( ) 
{ 
  std::cout << "Zadaj ascii prechod (.txt)" << std::endl;
  std::string fileName;
  readDirectory(".txt");  
  std::cout << space << std::endl;
  getline( std::cin , fileName);
  if ( fileName.substr(fileName.size()-FORMAT_LEN,4) != ".txt")
    throw std::invalid_argument("Toto neni .txt");
  if(!checkIfFileValid(path+fileName))
      throw std::invalid_argument("Nefunkcny txt, skus iny");
  std::ifstream txtFile;
  std::string line;
  txtFile.open(path+fileName);
  while ( std::getline (txtFile, line)){
      asciiLevel+=line;
  }
  std::cout << asciiLevel << std::endl;
  
}

CImage CFileReader::readPNG(const std::string &imageName)  
{
    FILE * imageFile = fopen(imageName.c_str() , "r");
    png_structp pngStr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pngInfo = png_create_info_struct(pngStr);
    png_init_io(pngStr, imageFile);
    png_read_png(pngStr, pngInfo, PNG_TRANSFORM_IDENTITY , NULL);
    imageMatrix = converter->toGrayScale(pngStr,pngInfo);
    converter = new CTool (asciiLevel);
    CImage image = CImage( imageMatrix, converter , imageName.substr(path.size(),imageName.size()));
    fclose(imageFile);
  
    return image;
}

