# zorro-bitfinex-plugin
Bitfinex broker plugin for Zorro Trading Automation 1.50

Work in progress, plugin not functional yet

## How to build the project
1. Create Visual Studio dll project, as described [here](http://zorro-trader.com/manual/en/brokerplugin.htm).
2. Name the project ZorroBitfinexPlugin.
3. Copy & replace source code folder content with repository content.
4. Add `trading.h` file to VS project.
5. Use NuGet to install **cpprestsdk 140** as described [here](https://github.com/Microsoft/cpprestsdk/wiki/How-to-use-the-C---Rest-SDK-NuGet-package).

## SETUP
Create file named `ZorroBitfinexPlugin_keys.txt` in `Zorro/Plugin` folder. Paste your bitfinex keys into the file, api key in first line, api secret in second.

## Resources
- [Cpprestsdk Getting Started Tutorial](https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial)
- [How to use the C Rest SDK NuGet package](https://github.com/Microsoft/cpprestsdk/wiki/How-to-use-the-C---Rest-SDK-NuGet-package)
- [Zorro Broker API documentation](http://zorro-trader.com/manual/en/brokerplugin.htm)
