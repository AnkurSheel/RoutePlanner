using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FontCreator
{
	class FontDeclaration
	{
		public string m_Language;          //the column index of the language to export
		public string m_FileName;          //name of the exported file
		public int m_FontSize;             //Size of the font to export e.g. Font 12
		public string m_FontName;          //Name of the font to export e.g. Arial
		public bool m_Bold;                //true if this font is to be exported as bold
		public int m_Outline;              //width in pixels of the outline to apply to this font
		public int m_TextureWidth;         //width of the texture in pixels e.g. 512X512, not that all characters need to fit on the one texture
	}
}
