#/bin/env python
# -*- coding: utf-8 -*-
import logging

#logging.basicConfig(level=logging.DEBUG)
logging.basicConfig(filename='./test.log',level=logging.DEBUG)

logging.debug("======================")
logging.debug("======================")
logging.debug("디버깅용 로그~~")
logging.info("도움이 되는 정보를 남겨요~")
logging.warning("주의해야되는곳!!")
logging.error("에 러!!!~~")
logging.critical("심각한 에러!!")
