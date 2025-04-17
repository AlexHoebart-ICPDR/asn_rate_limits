# ASN Rate Limits

This module addresses the situation when 
* crawlers do not identify themselves as a bot (pretending to be human-traffic) and 
* rapidly crawl your site from hundreds of unique IPs and user agent strings bringing your server to its limits and slowing it down.

Such crawler traffic usually comes in under a single autonomous system number (ASN), identifying the network of the cloud-computing platform the crawler was running from.

In such situation, the module 
* monitors your site on every cron run:
    * checks if your server load is above defined limits
    * checks your recent access log entries and identifies IPs belonging to the same ASN and calculates their accumulated number of hits and execution time 
* blocks all IPs from an ASN which overuses your server based on defined limits. 

## Configuration

Adapt the settings under Configuration - User Accounts - ASN Rate Limits.

## Installation

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.
- Requ on [IP address blocking](https://backdropcms.org/project/ip_blocking) and [Statistics](https://backdropcms.org/project/statistics) modules.

## Issues

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/AlexHoebart-ICPDR/asn_rate_limites/issues.

## Current Maintainers

- [Alex Höbart](https://github.com/AlexHoebart-ICPDR).
- Additional maintainers are welcomed.

## Credits

Inspired by the following modules:

- [Crawler Rate Limit](https://www.drupal.org/project/crawler_rate_limit) module for Drupal by [vaish](https://www.drupal.org/u/vaish).
- [Antiscan](https://backdropcms.org/project/antiscan) module for Backdrop by [Vladimir](https://github.com/findlabnet/)

## License

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.
