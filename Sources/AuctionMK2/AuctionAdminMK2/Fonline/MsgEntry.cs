using System;
using System.Collections.Generic;
using System.Text;

namespace AuctionAdminMK2.Fonline
{
	public class MsgEntry
	{
		private readonly uint _id;
		private readonly string _text;

		public MsgEntry(uint id, string text)
		{
			_id = id;
			_text = text;
		}

		public uint Id
		{
			get { return _id; }
		}
		
		public string Text
		{
			get { return _text; }
		}
	}
}
