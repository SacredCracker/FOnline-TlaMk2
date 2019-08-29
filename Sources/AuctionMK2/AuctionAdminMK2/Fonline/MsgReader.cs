using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;


namespace AuctionAdminMK2.Fonline
{
	/// <summary>
	/// Reader for msg files.
	/// </summary>
	public sealed class MsgReader : IDisposable
	{
		private const string MsgEntryRegex = @"^{(?<id>[0-9]+)}{}{(?<value>[^}]*)}";

		private bool _disposed;
		private TextReader _reader;

		public MsgReader(string path)
		{
            _reader = new StreamReader(path, Encoding.GetEncoding("Windows-1251"));
			_disposed = false;
		}

		public MsgReader(Stream stream)
		{
			if (stream == null)
				throw new ArgumentNullException("stream");

			_reader = new StreamReader(stream);
			_disposed = false;
		}

		public MsgReader(TextReader reader)
		{
			if (reader == null)
				throw new ArgumentNullException("reader");

			_reader = reader;
			_disposed = false;
		}

		public void Dispose()
		{
			Dispose(true);
		}

		private void Dispose(bool disposing)
		{
			if (!_disposed)
			{
				if (disposing && _reader != null)
				{
					_reader.Dispose();
				}

				_reader = null;
				_disposed = true;
			}
		}

		public MsgEntry ReadNextEntry(string regEx)
		{
			if (_disposed)
				throw new ObjectDisposedException("MsgReader was disposed");

			// buffer to store current entry contents
			var buffer = new StringBuilder();

            Regex regex = new Regex(regEx);

			Match match;
			do
			{
				// read line
				string nextLine = _reader.ReadLine();
				// end of reader
				if (nextLine == null)
					break;

				// append line to buffer
				buffer.AppendLine(nextLine);
				
				// match buffer contents
				match = regex.Match(buffer.ToString());

				if (match.Success)
				{
					uint id = uint.Parse(match.Groups["id"].Value);
					string value = match.Groups["value"].Value;
					return new MsgEntry(id, value);
				}
			} while (!match.Success); // try with next line (to handle multiline entries)

			return null;
		}
	}
}
