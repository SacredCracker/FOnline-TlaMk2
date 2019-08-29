using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AuctionAdminMK2.Fonline
{
    public class LstReader
    {
        private const string IdRegex = @"(?<id>[0-9]+)";
		private const string NameRegex = @"(?<name>[_a-zA-Z0-9]+)";

		private const string ItemRegex =
			@"^" + IdRegex + @"\s+" + NameRegex;

    }
}
