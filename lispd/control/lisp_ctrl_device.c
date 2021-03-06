/*
 *
 * Copyright (C) 2011, 2015 Cisco Systems, Inc.
 * Copyright (C) 2015 CBA research group, Technical University of Catalonia.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#include "../lispd_external.h"
#include "../lib/packets.h"
#include "../lib/sockets.h"
#include "lisp_ctrl_device.h"


static ctrl_dev_class_t *reg_ctrl_dev_cls[4] = {
        &xtr_ctrl_class,
        &ms_ctrl_class,
        &xtr_ctrl_class,/* RTR */
        &xtr_ctrl_class,/* MN */
};

inline lisp_dev_type_e
lisp_ctrl_dev_mode(lisp_ctrl_dev_t *dev){
    return dev->mode;
}
inline lisp_ctrl_t *
lisp_ctrl_dev_get_ctrl_t(lisp_ctrl_dev_t *dev){
    return dev->ctrl;
}

static ctrl_dev_class_t *
ctrl_dev_class_find(lisp_dev_type_e type)
{
    return(reg_ctrl_dev_cls[type]);
}

int
ctrl_dev_recv(lisp_ctrl_dev_t *dev, lbuf_t *b, uconn_t *uc)
{
    return(dev->ctrl_class->recv_msg(dev, b, uc));
}

void
ctrl_dev_run(lisp_ctrl_dev_t *dev)
{
    dev->ctrl_class->run(dev);
}

int
ctrl_dev_create(lisp_dev_type_e type, lisp_ctrl_dev_t **devp)
{
    lisp_ctrl_dev_t *dev;
    ctrl_dev_class_t *class;

    *devp = NULL;

    /* find type of device */
    class = ctrl_dev_class_find(type);
    dev = class->alloc();
    dev->mode =type;
    dev->ctrl_class = class;
    dev->ctrl_class->construct(dev);
    ctrl_dev_set_ctrl(dev, lctrl);
    *devp = dev;
    return(GOOD);
}

void
ctrl_dev_destroy(lisp_ctrl_dev_t *dev)
{
    if (!dev) {
        return;
    }

    dev->ctrl_class->destruct(dev);
    dev->ctrl_class->dealloc(dev);
}

int
send_msg(lisp_ctrl_dev_t *dev, lbuf_t *b, uconn_t *uc)
{
    return(dev->ctrl->control_data_plane->control_dp_send_msg(dev->ctrl, b, uc));
}


int
ctrl_if_event(lisp_ctrl_dev_t *dev, char *iface_name, lisp_addr_t *old_addr,
        lisp_addr_t *new_addr, uint8_t status)
{
    dev->ctrl_class->if_event(dev, iface_name, old_addr, new_addr, status);
    return(GOOD);
}

fwd_info_t *
ctrl_dev_get_fwd_entry(lisp_ctrl_dev_t *dev, packet_tuple_t *tuple)
{
    return(dev->ctrl_class->get_fwd_entry(dev, tuple));
}

inline lisp_dev_type_e
ctrl_dev_mode(lisp_ctrl_dev_t *dev)
{
    return (dev->mode);
}

inline lisp_ctrl_t *
ctrl_dev_ctrl(lisp_ctrl_dev_t *dev)
{
    return (dev->ctrl);
}

int
ctrl_dev_set_ctrl(lisp_ctrl_dev_t *dev, lisp_ctrl_t *ctrl)
{
    dev->ctrl = ctrl;
    ctrl_register_device(ctrl, dev);
    return(GOOD);
}

char *
ctrl_dev_type_to_char(lisp_dev_type_e type)
{
    static char device[15];
    *device='\0';
    switch (type){
    case xTR_MODE:
        strcpy(device,"xTR");
        break;
    case MS_MODE:
        strcpy(device,"Map Server");
        break;
    case RTR_MODE:
        strcpy(device,"RTR");
        break;
    case MN_MODE:
        strcpy(device,"Mobile Node");
        break;
    default:
        strcpy(device,"Unknown");
        break;
    }
    return (device);
}
