using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcelLibrary.SpreadSheet;
using System.Xml;
using System.IO;

namespace FontCreator
{
	class Program
	{
		private static Workbook m_pWorkBook = null;
		private static List<StringKeys> m_pDictionaryList = new List<StringKeys>();
		private static List<FontDeclaration> m_pFontList = new List<FontDeclaration>();

		static void Main(string[] args)
		{
			string file = "Test.xls";
			m_pWorkBook = Workbook.Load(file);

			InitializeDictionaryListFromFirstRow();
			ReadAllStringsIntoDictionaries();
			WriteStringsToBinary();

			ReadBinaryIntoDictionary();
			WriteStringsToXML();

			XmlWriterSettings pSettings = new XmlWriterSettings();
			pSettings.Indent = true;

			ReadFontDeclaration();
			WriteAllBmFontConfigFiles();
		}

		private static void InitializeDictionaryListFromFirstRow()
		{
			Worksheet pCurrentWorkSheet = m_pWorkBook.Worksheets[0];
			Row row = pCurrentWorkSheet.Cells.GetRow(0);
			Cell pCell;

			for (int colIndex = pCurrentWorkSheet.Cells.FirstColIndex; colIndex <= pCurrentWorkSheet.Cells.LastColIndex; colIndex++)
			{
				pCell = row.GetCell(colIndex);
				if (!pCell.IsEmpty)
				{
					StringKeys k = new StringKeys();
					k.language = pCell.StringValue;
					k.columnIndex = colIndex;
					k.dictionaryList = new Dictionary<string, string>();
					m_pDictionaryList.Add(k);
				}
			}
		}

		private static void ReadAllStringsIntoDictionaries()
		{
			Row pRow;
			Cell pCell;
			Cell pKey;
			string sKey;
			foreach (Worksheet pCurrentWorkSheet in m_pWorkBook.Worksheets)
			{
				foreach (StringKeys k in m_pDictionaryList)
				{
					for (int RowIndex = pCurrentWorkSheet.Cells.FirstRowIndex; RowIndex <= pCurrentWorkSheet.Cells.LastRowIndex; RowIndex++)
					{
						pRow = pCurrentWorkSheet.Cells.GetRow(RowIndex);
						pCell = pRow.GetCell(k.columnIndex);
						pKey = pRow.GetCell(1);
						sKey = pKey.StringValue.ToUpper();
						if (pKey.StringValue.Length > 0 && !k.dictionaryList.ContainsKey(sKey))
						{
							k.dictionaryList.Add(sKey, pCell.StringValue);
						}
					}
				}
			}
		}

		private static void WriteStringsToBinary()
		{
			foreach (StringKeys k in m_pDictionaryList)
			{
				//Console.WriteLine("Language " + k.language);
				using (BinaryWriter writer = new BinaryWriter(File.Open(k.language + "_strings.loc", FileMode.Create)))
				{
					writer.Write(k.dictionaryList.Count);

					foreach (KeyValuePair<string, string> pair in k.dictionaryList)
					{
						writer.Write(pair.Key.Length);
						writer.Write(Encoding.ASCII.GetBytes(pair.Key));
						writer.Write(pair.Value.Length);
						writer.Write(Encoding.Unicode.GetBytes(pair.Value));
					}
					writer.Close();
				}
			}
		}

		private static void ReadBinaryIntoDictionary()
		{
			foreach (StringKeys k in m_pDictionaryList)
			{
				k.dictionaryList.Clear();
				int pos = 0;
				using (BinaryReader reader = new BinaryReader(File.Open(k.language + "_strings.loc", FileMode.Open)))
				{
					int size = reader.ReadInt32();
					for (int i = 0; i < size; i++)
					{
						int idLength = reader.ReadInt32();
						byte[] bytes = reader.ReadBytes(idLength);
						string key = Encoding.ASCII.GetString(bytes);
						int valueLength = reader.ReadInt32();
						bytes = reader.ReadBytes(valueLength * 2);
						string value = Encoding.Unicode.GetString(bytes);
						k.dictionaryList.Add(key, value);
					}
					reader.Close();
				}
			}
		}

		private static void WriteStringsToXML()
		{
			XmlWriterSettings pSettings = new XmlWriterSettings();
			pSettings.Indent = true;

			foreach (StringKeys k in m_pDictionaryList)
			{
				//Console.WriteLine("Language " + k.language);
				using (XmlWriter writer = XmlWriter.Create(k.language + "_strings.xml", pSettings))
				{
					writer.WriteStartDocument();
					writer.WriteStartElement("Strings");
					foreach (KeyValuePair<string, string> pair in k.dictionaryList)
					{
						writer.WriteStartElement("string");
						writer.WriteAttributeString("id", pair.Key);
						writer.WriteAttributeString("value", pair.Value);
						writer.WriteEndElement();
					}
					writer.WriteEndElement();
					writer.WriteEndDocument();
				}
			}
		}

		private static void ReadFontDeclaration()
		{
			using (XmlReader reader = XmlReader.Create("Fonts.xml"))
			{
				while (reader.Read())
				{
					if (reader.Name == "Font")
					{
						FontDeclaration font = new FontDeclaration();
						font.m_Language = reader.GetAttribute("Language");
						font.m_FileName = reader.GetAttribute("ConfigFileName");
						font.m_FontName = reader.GetAttribute("Name");
						font.m_Bold = (reader.GetAttribute("Bold") == "True");
						font.m_FontSize = int.Parse(reader.GetAttribute("Size"));
						font.m_Outline = int.Parse(reader.GetAttribute("Outline"));
						font.m_TextureWidth = int.Parse(reader.GetAttribute("TextureWidth"));

						m_pFontList.Add(font);
					}
				}
			}
		}

		private static void WriteAllBmFontConfigFiles()
		{
			foreach (FontDeclaration font in m_pFontList)
			{
				//instantiate a list for storing unicode characters
				HashSet<char> pCharacterList = new HashSet<char>();

				CreateCharacterLists(ref pCharacterList, font.m_Language);

				//Create a stream Writer
				WriteBmConfigFile(font, pCharacterList);
			}
		}

		private static void CreateCharacterLists(ref HashSet<char> pCharacterList, string languageType)
		{
			//add the 256 default ascii characters
			for (int i = 0; i < 256; i++)
			{
				pCharacterList.Add((char)i);
			}

			//if the language is european (english/french/spanish/german/italian/portuguese)
			if (languageType == "European")
			{
				AddToCharacterList("English", ref pCharacterList);
				AddToCharacterList("French", ref pCharacterList);
			}
			else if (languageType == "Japanese")
			{
				AddToCharacterList("Japanese", ref pCharacterList);
			}
		}

		private static void AddToCharacterList(string language, ref HashSet<char> pCharacterList)
		{
			StringKeys k = m_pDictionaryList.Find(x => x.language == language);
			foreach (KeyValuePair<string, string> pair in k.dictionaryList)
			{
				//get each character in the value
				foreach (char c in pair.Value)
				{
					pCharacterList.Add(c);
				}
			}
		}

		private static void WriteBmConfigFile(FontDeclaration font, HashSet<char> pCharacterList)
		{
			using (StreamWriter writer = new StreamWriter(File.Open(font.m_FileName, FileMode.Create)))
			{
				writer.WriteLine("# AngelCode Bitmap Font Generator configuration file");
				writer.WriteLine("fileVersion=1");
				writer.WriteLine("");
				writer.WriteLine("# font settings");
				writer.WriteLine("fontName=" + font.m_FontName);
				writer.WriteLine("charSet=0");
				writer.WriteLine("fontSize=" + font.m_FontSize);
				writer.WriteLine("aa=1");
				writer.WriteLine("scaleH=100");
				writer.WriteLine("useSmoothing=1");
				writer.WriteLine("isBold=" + ((font.m_Bold) ? 1 : 0));
				writer.WriteLine("isItalic=0");
				writer.WriteLine("useUnicode=1");
				writer.WriteLine("disableBoxChars=1");
				writer.WriteLine("outputInvalidCharGlyph=0");
				writer.WriteLine("");
				writer.WriteLine("# character alignment");
				writer.WriteLine("paddingDown=" + font.m_Outline);
				writer.WriteLine("paddingUp=" + font.m_Outline);
				writer.WriteLine("paddingRight=" + font.m_Outline);
				writer.WriteLine("paddingLeft=" + font.m_Outline);
				writer.WriteLine("spacingHoriz=" + (1 + font.m_Outline));
				writer.WriteLine("spacingVert=" + (1 + font.m_Outline));
				writer.WriteLine("");
				writer.WriteLine("# output file");
				writer.WriteLine("outWidth=" + font.m_TextureWidth);
				writer.WriteLine("outHeight=" + font.m_TextureWidth);
				writer.WriteLine("outBitDepth=32");
				writer.WriteLine("fontDescFormat=1");
				writer.WriteLine("fourChnlPacked=0");
				writer.WriteLine("textureFormat=png");
				writer.WriteLine("textureCompression=0");
				writer.WriteLine("alphaChnl=2");
				writer.WriteLine("redChnl=0");
				writer.WriteLine("greenChnl=0");
				writer.WriteLine("blueChnl=0");
				writer.WriteLine("invA=0");
				writer.WriteLine("invR=0");
				writer.WriteLine("invG=0");
				writer.WriteLine("invB=0");
				writer.WriteLine("");
				writer.WriteLine("# outline");
				writer.WriteLine("outlineThickness=" + 0);//a_oFont.m_iOutline);
				writer.WriteLine("");
				writer.WriteLine("# selected chars");

				writer.Write("chars=");

				int iLineCount = 0;

				foreach (char c in pCharacterList)
				{
					//write out a line for each key that creates a # define that can be used in C++
					writer.Write((int)c + ",");

					//once we've written 10
					if (iLineCount++ > 10)
					{
						//go to the next line
						writer.Write("\nchars=");
						iLineCount -= 10;
					}
				}
				//close the binary writer
				writer.Close();
			}
		}
	}
}