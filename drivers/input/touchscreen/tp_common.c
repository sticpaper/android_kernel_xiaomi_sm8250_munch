#include <linux/input/tp_common.h>

struct kobject *touchpanel_kobj;
#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
struct kobject *touch_game_kobj;
#endif

#define TS_ENABLE_FOPS(type)                                        \
int tp_common_set_##type##_ops(struct tp_common_ops *ops)           \
{                                                                   \
	static struct kobj_attribute kattr =                        \
		__ATTR(type, (S_IWUSR | S_IRUGO), NULL, NULL);      \
	kattr.show = ops->show;                                     \
	kattr.store = ops->store;                                   \
	return sysfs_create_file(touchpanel_kobj, &kattr.attr);     \
}

#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
#define TOUCHGAME_FOPS(type)                                        \
int tp_common_set_##type##_ops(struct tp_common_ops *ops)           \
{                                                                   \
	static struct kobj_attribute kattr =                        \
		__ATTR(type, (S_IWUSR | S_IRUGO), NULL, NULL);      \
	kattr.show = ops->show;                                     \
	kattr.store = ops->store;                                   \
	return sysfs_create_file(touch_game_kobj, &kattr.attr);     \
}
#endif

TS_ENABLE_FOPS(double_tap)
TS_ENABLE_FOPS(fod_status)

static int __init tp_common_init(void)
{
	touchpanel_kobj = kobject_create_and_add("touchpanel", NULL);
	if (!touchpanel_kobj)
		return -ENOMEM;
#ifdef CONFIG_TOUCHSCREEN_XIAOMI_GAMEMODE_NODE
	touch_game_kobj = kobject_create_and_add("touch_game", touchpanel_kobj);
	if (!touch_game_kobj)
		return -ENOMEM;
#endif

	return 0;
}
core_initcall(tp_common_init);
