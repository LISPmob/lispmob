#
# Copyright (C) 2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lispmob
PKG_REV:=6f302efbcb27da85ce9835328023ae2cad8378bf
PKG_VERSION:=0.3.1
PKG_RELEASE:=3

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=git://github.com/LISPmob/lispmob.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)

include $(INCLUDE_DIR)/package.mk

define Package/lispd/default
  MAINTAINER:=Vasileios Lakafosis <lakafv@gmail.com>
  URL:=http://lisp.cisco.com/
endef

define Package/lispd
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Locator/ID separation protocol (using TUN)
  URL:=https://github.com/LISPmob
  DEPENDS:= +librt +libopenssl +confuse +kmod-tun +uci +kmod-ipv6 +luci
  $(call Package/lispd/default)
endef

define Package/lispd/description
  This packet provides support for the Locator-ID support protocol.
endef



define Build/Compile
	$(call Build/Compile/Default,platform=openwrt)
endef



define Package/lispd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lispd/lispd $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/openWRT/lispd.uci.example $(1)/etc/config/lispd
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lispd/openwrt.init.script $(1)/etc/init.d/lisp
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/controller/lisp
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/openWRT/controller-lisp.lua $(1)/usr/lib/lua/luci/controller/lisp/lisp.lua
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/model/cbi/lisp
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/openWRT/model-cbi-lisp.lua $(1)/usr/lib/lua/luci/model/cbi/lisp/lisp.lua
endef

$(eval $(call BuildPackage,lispd))