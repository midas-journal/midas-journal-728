#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSimpleFilterWatcher.h"
#include "itkMetaDataObject.h"



int main(int argc, char * argv[])
{

  if( argc != 2 )
    {
    std::cerr << "usage: " << argv[0] << " intput " << std::endl;
    std::cerr << " input: the input image" << std::endl;
    // std::cerr << "  : " << std::endl;
    exit(1);
    }

  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;


  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  typedef itk::MetaDataDictionary   DictionaryType;
  typedef itk::MetaDataObject< std::string > MetaDataStringType;

  const  DictionaryType & dictionary = reader->GetImageIO()->GetMetaDataDictionary();
  DictionaryType::ConstIterator itr = dictionary.Begin();
  DictionaryType::ConstIterator end = dictionary.End();
  while( itr != end )
    {
    itk::MetaDataObjectBase::Pointer  entry = itr->second;

    MetaDataStringType::Pointer entryvalue = 
      dynamic_cast<MetaDataStringType *>( entry.GetPointer() );
    if( entryvalue )
      {
      std::string tagkey   = itr->first;
      std::cout << "MetaDataDict " << tagkey << ": " << entryvalue->GetMetaDataObjectValue() << std::endl;

      }

    ++itr;
    }

  return 0;
}

