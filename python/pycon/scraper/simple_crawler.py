#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

'''
See also:
- Scrapy: framework
- lxml (faster parsing)
- BeautifulSoup: broken HTML
- html5lib
- xpath (alt. to CSS selectors)
- permanent storage such as Redis
- task queue like Celery
'''

from __future__ import unicode_literals
from urlparse import urljoin

import gevent
from gevent import monkey; monkey.patch_all()
from pyquery import PyQuery
import requests


def fetch_page(url):
    r = requests.get(url)
    return r.text


def list_from_html(html, selector):
    d = PyQuery(html)
    items = d(selector)
    return items


def extract_article(item, baseurl=''):
    title = item.find('h3').find('a')
    url = urljoin(baseurl, PyQuery(title).attr['href'])

    subpage_html = fetch_page(url)
    video = PyQuery(subpage_html)('.video').find('iframe')
    video_url = urljoin(baseurl, PyQuery(video).attr['src'])

    return {
        'title': title.text,
        'summary': item.find('p').text,
        'url': url,
        'video': video_url,
    }


def print_article(article):
    print '''Title: {title}
Summary: {summary}
URL: {url}
Video: {video}
'''.format(**article)


def crawl_page(url):
    html = fetch_page(url)
    items = list_from_html(html, 'li[class*="NE=a:onl"]')
    jobs = [gevent.spawn(extract_article, item, baseurl=url) for item in items]
    gevent.joinall(jobs)
    articles = [job.value for job in jobs]
    return articles


if __name__ == '__main__':
    url = 'http://music.naver.com/onStage/onStageReviewList.nhn'
    articles = crawl_page(url)
    map(print_article, articles)